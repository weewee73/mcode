#/bin/bash

## array for monitor process 
declare -ar proc=(SYSTEM_TOTAL)
declare -ar cpu_warn=(        90            90       90         90    90      90       90       90         90       90           90         90     90     90      90)
declare -ar mem_error=(  1024000       1024000   120000     120000 120000  120000   120000   120000     120000   120000       120000     120000 120000 120000  120000)
declare -ar mem_warn=(   1624000       1624000    60000       60000 60000   60000    60000    60000      60000    60000        60000      60000  60000  60000   60000)
declare -ar fs_error=(       512           512      512        512   512     512      512      512        512      512          512        512    512    512     512)
declare -ar fs_warn=(        128           128      128        128   128     128      128      128        128      128          128        128    128    128     128)

## array for every process
declare -a a_pid a_pcpu a_pmem a_rss a_vsz a_fs a_comm a_args

## array for every monitor process
declare -a monitor monitor_key 

declare -ar directory=(
.
)

db_max=50000 
db_tables=(

)

declare -r log="/log"
declare -r f_log="$log/alarm.log"

f_ps=`mktemp ps.XXXXXXXXXXXX` || exit 1
f_lsof=`mktemp lsof.XXXXXXXXXXXX` || exit 1
trap 'rm -f $f_ps $f_lsof' EXIT


ERROR="\033[1;31m" OK="\033[1;32m" WARN="\033[1;33m" END="\033[0m"



function log()
{
    log_time=$(date "+%Y-%m-%d %k:%m:%S")
    log_msg=

    [[ -f $f_log ]] || touch $f_log 
    echo
}

function db_log()
{
    local sql
    
    mysql --execute="$sql"
}

function check_db()
{
    local count msg db_name tb_name
    local bakup="$log/bakup/mysql"
    
    for table in ${db_tables[@]}
    do
        count=`mysql --batch --skip-column-name --execute="select count(*) from $table;"`
        if [[ "$count" -gt "$db_max" ]]; then
            msg="table $table has more than $db_max records[$count]!"
            log "warn" "db" "0" "$msg"
            
            db_name=${table#*.}
            tb_name=${table%.*}
            mysqldump $dbname $tb_name >"$backup/$table.sql"
            mysql --execute="delete from $table;"

            log "OK" "db" "0" "$msg"
            db_log ok
        fi
    done
}

function show_db()
{
    local format="%-32s %8s\n"

    printf "$format" "TABLE" "COUNT"
    for table in ${db_tables[@]}
    do
        count=`mysql --batch --skip-column-name --execute="select count(*) from $table;"`
        if [[ "$count" -gt "$db_max" ]]; then
            format="$WARN%-32 %8s$END\n"
        fi
        printf "$format" $table $count
    done
}

function action_log()
{
    local filename="log_"$(date "+%Y-%m-%d_%k-%m-%S")
    local bakup="$log/bakup/log"

    rm -f "$bakup/*"
    [[ -d "$bakup" ]] || mkdir -p "$bakup"
    cd "$log" 
    find . -name "*_bak.log" -o -name "alarm.log" | xargs tar -cvj --remove-files $filename.tar.bz2
    mv *.tar.bz2 $bakup
}

##Delete oldest files from the specified directory. 
function file_delete()
{
    local dir=$1 warn=$2 cnt=10

    while [[ $size -ge $warn ]]
    do
        find "$dir" -maxdepth 1 -type f | xargs ls -1rt | tail -n +$cnt | xargs rm -f 
        size=$(du -sm $dir | cut -f 1)
    done

}

function check_directory()
{
    local warn=1000 #1G
    local i=0 msg files
    for key in ${directory[@]}
    do
        if [[  -e "$key" ]]; then
            files[((i++))]=$key
        else
            msg="$key is not exists!"
            log "WARNING" "dir" "0" "$msg"
            db_log
        fi
    done

    du -sm ${files[@]} | while read size dir
    do
        if [[ $size -ge $warn ]];then
            msg="$dir has more than ${warn}M [${size}M]!"
            log "WARNING" "dir" "0" "$msg"

            if [[ $dir = $log ]];then
                action_log
            fi

            file_delete $dir $((warn/2))
            log "OK" "dir" "0" "$msg"
            db_db ok
        fi
    done

}

function show_directory()
{
    du -sh ${directory[@]}
}


function check_disk()
{
    local warn=10 msg flag=0
    # Filesystem            Size  Used Avail Use% Mounted on
    df -h | sed '1d' | while read fiesystem size used avail use mount
    do
        if [[ ${use%%%} -ge $warn ]];then
            msg="$fiesystem mount on $mount used more than $warn% [$used/$size]! "
            log "WARNING" "disk" "0" "$msg"

            if [[ $mount == "/"  ]];then
                check_directory
                log "OK" "disk" "0" "$msg"
                db_log ok
            else
                db_log
            fi
        fi
    done
}


function show_disk()
{
    df -h
}

function check_memory()
{
    local flag=0

    flag=`free -o | awk '/Mem:/ {if($3/$2 > 0.9) print 1;else print 0}'`
    if [[ $flag -eq 0 ]];then
        return
    fi

    log "WARNING" "memory" "0" "System Memory exceeds 90%!"
    sync && echo 3 > /proc/sys/vm/drop_caches
    flag=`free -o | awk '/Mem:/ {if($3/$2 > 0.9) print 1;else print 0}'`
    if [[ $flag -eq 0 ]]; then
        log "OK" "memory" "0" "System Memory exceeds 90%!"
        db_log ok
    elif [[ $flag -eq 1 ]]; then
        log "ERROR" "memory" "1" "System Memory exceeds 90%!"
        db_log
    fi
}

function action_proc()
{
    if [[ -n $1 && ! $1 -eq 0 ]];then
        echo kill $1
        #kill -9 $1
    elif [[ -n $1 && $1 -eq 0 ]];then
        echo stop...
    fi

    #action...
}


function process()
{
    ps -eo pid,pcpu,pmem,rss,vsz,comm,args --sort pid  | awk '
    NR!=1{
         cpu+=$2; mem+=$3; rss+=$4; vsz+=$5
         print $0
    }
    END{
        print "0 " cpu " " mem " " rss " " vsz " SYSTEM_TOTAL " "SYSTEM_TOTAL"
    }' >$f_ps

    lsof -F fc | awk '
    {
        if (/^p/) 
            pid=substr($0,2)
        else if (/^c/) 
            comm[pid]=substr($0,2)
        else if (/^f/) 
            process[pid]++
    } 
    END{
        for (pid in process) 
            printf "%8d %8d %8s\n", pid, process[pid], comm[pid] 
    }' | sort -n -k2 >$f_lsof

    while read pid pcpu pmem rss vsz comm args
    do
        a_pid[$pid]=$pid
        a_pcpu[$pid]=$pcpu
        a_pmem[$pid]=$pmem
        a_rss[$pid]=$rss
        a_vsz[$pid]=$vsz
        a_fs[$pid]=0
        a_comm[$pid]=$comm
        a_args[$pid]=$args

        #set proc pid
        for key in ${!proc[@]}
        do
            if [[ "$args" == *"${proc[$key]}"* ]];then
                monitor[$key]=$pid
                monitor_key[$pid]=$key
                break
            fi
        done
        
    done<$f_ps

    while read pid fs comm
    do
        if [[ -n "${a_pid[$pid]}" ]];then
            a_fs[$pid]=$fs
        fi
    done<$f_lsof

}

function check_process()
{
    local msg key pid flag_warn flag_error

    process
    for key in ${!proc[@]}
    do
        pid=${monitor[key]}
        flag_warn=0 
        flag_error=0
        msg="${proc[key]}"

        if [[  -n "$pid" ]];then
            msg=$msg"[pid]"

            ## CPU
            if [[ ${a_pcpu[pid]%.*} -ge ${cpu_warn[key]} ]];then
                msg=$msg" CPU add up to ${a_pcpu[pid]}!"
                if [[ ${a_pcpu[pid]%.*} -lt ${cpu_error[key]} ]];then
                    flag_warn=1
                else
                    flag_error=1
                fi

            fi

            ## Memory
            if [[ ${a_rss[pid]} -ge ${mem_warn[key]} ]];then
                msg=$msg" Memory add up to $((${a_rss[pid]}/1024))M!"
                if [[ ${a_rss[pid]} -lt ${mem_error[key]} ]];then
                    flag_warn=1
                else
                    flag_error=1
                fi
            fi

            ## Open files
            if [[ ${a_fs[pid]} -ge ${fs_warn[key]} ]];then
                msg=$msg" Open files  has ${a_fs[pid]}!"
                if [[ ${a_fs[pid]} -lt ${fs_error[key]} ]];then
                    flag_warn=1
                else
                    flag_error=1
                fi
            fi

           # if [[ $pid -eq 0 ]];then
           #     echo
           # el
            if [[ $flag_error == 1 ]];then
                log "ERROR" "proc" "1" "$msg"
                action_proc "$pid"
                log OK "proc" "0" "$msg"
                db_log ok
            elif [[ $flag_warn == 1 ]];then
                log "WARNING" "proc" "0" "$msg"
                db_log
            fi

        else
            msg=$msg" is not running!"
            log "ERROR" "proc" "0" "$msg"
            action_proc
            log OK "proc" "0" "$msg"
            db_log ok
        fi
    done

}

function color_process()
{

    local msg key pid flag_warn flag_error format

    pid=$1
    key=${monitor_key[pid]}

    if [[ -z $key ]];then
        printf "%8s %8s %8s %8s %8s %8s\t%-8s\n" $pid ${a_pcpu[pid]} ${a_pmem[pid]} ${a_rss[pid]} ${a_vsz[pid]} ${a_fs[pid]} ${a_comm[pid]}
        return
    fi

    flag_warn=0 
    flag_error=0
    format="%8s" #pid

    if [[ ${a_pcpu[pid]%.*} -lt ${cpu_warn[key]} ]];then
        format=$format" %8s"
    else
        format=$format" $WARN%8s$END" #pcpu
        flag_warn=1
    fi

    if [[ ${a_rss[pid]} -lt ${mem_warn[key]} ]];then
        format=$format" %8s %8s"
    elif [[ ${a_rss[pid]} -lt ${mem_error[key]} ]];then
        format=$format" $WARN%8s %8s$END"
        flag_warn=1
    else
        format=$format" $ERROR%8s %8s$END" #pmem rss
        flag_error=1
    fi

    format=$format" %8s" #vsz

    if [[ ${a_fs[pid]} -lt ${fs_warn[key]} ]];then
        format=$format" %8s"
    elif [[ ${a_fs[pid]} -lt ${fs_error[key]} ]];then
        format=$format" $WARN%8s$END"
        flag_warn=1
    else
        format=$format" $ERROR%8s$END"
        flag_error=1
    fi

    if [[ "$flag_warn" == 0 && "$flag_error" == 0 ]];then
        format=$format"\t$OK%-8s$END\n"
    elif [[ "$flag_error" == 0 ]];then
        format=$format"\t$WARN%-8s$END\n"
    else
        format=$format"\t$ERROR%-8s$END\n" #proc name
    fi

    printf "$format" $pid ${a_pcpu[pid]} ${a_pmem[pid]} ${a_rss[pid]} ${a_vsz[pid]} ${a_fs[pid]} ${proc[key]}
}


function show_process()
{

    printf "\n%8s %8s %8s %8s %8s %8s\t%-8s\n" "PID" "CPU%" "MEM%" "RSS(K)" "VSZ(K)" "OFS" "COMM"
    for key in ${!proc[@]}
    do
        pid=${monitor[$key]}
        if [[  -n "$pid" ]];then
            color_process $pid
        else
            printf "$ERROR%8s %8s %8s %8s %8s %8s\t%-8s$END\n" "-" "-" "-" "-" "-" "-" ${proc[key]}
        fi
    done
}


function sort_process()
{
    local key n=10

    if [[ "$1" == "-c" || "$1" == "-cpu" ]];then
        key=2
    elif [[ "$1" == "-m" || "$1" == "-mem" ]];then
        key=4
    elif [[ "$1" == "-f" || "$1" == "-file" ]];then
        key=6
    else
        key=4
    fi

    if [[ -n "$2" ]];then
        n=$2
    fi

    printf "\n%8s %8s %8s %8s %8s %8s\t%-8s\n" "PID" "CPU%" "MEM%" "RSS(K)" "VSZ(K)" "OFS" "COMM"
    for pid in ${!a_pid[@]}
    do
        printf "%8s %8s %8s %8s %8s %8s %8s\n" $pid ${a_pcpu[$pid]} ${a_pmem[$pid]} ${a_rss[$pid]} ${a_vsz[$pid]} ${a_fs[$pid]} ${a_comm[$pid]}
    done | sort -nr -k $key | head -n $n | while read pid others
        do
            color_process $pid
        done
}

function usage()
{
    cat <<EOF
Usage: `basename $0` [OPTION]
    -m monitor model 
    -p[monitor, cpu, mem, of] only show process information
        monitor:  only show specify pragrams
        cpu:  show the top10 cpu usage
        mem:  show the top10 memory usage
        of:   show the top10 open files
    -s only show directory space.
    -t only show database infomation.
    -d only show disk space.
EOF
}



#### main() ####

NO_ARGS=0
E_OPTERROR=85
RET=0

if [ $# -eq "$NO_ARGS" ]; then
    usage
	exit $E_OPTERROR
fi

while getopts "dmp:st" option
do
	case $option in
		m) 
            check_process
            check_memory
            check_disk
            check_directory
            check_db
            ;;
		d)
            show_disk
            ;;
		p)
            process
            case ${OPTARG} in
                cpu) sort_process -cpu;;
                mem) sort_process -mem;;
                of ) sort_process -f;;
                *  ) show_process;;
            esac
            ;;
		s)
            show_directory
            ;;
		t)
            show_db
            ;;
		*)  usage
            ;;	
	esac
done

shift $(($OPTIND - 1))

exit $RET

