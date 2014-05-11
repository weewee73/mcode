#/bin/bash

SUCC=0
FAIL=255 #return -- -1;Exit codes should be in the range 0-255.

function usage()
{
    cat <<EOF
Usage: `basename $0` [-f configfile]
    The default configfile is merge.conf
    FILE FORMAT:
        new_file    file_1:offset_1,file_2:offset_2[,...]     [new_char1:offset_char1[,...]]
        For example:
        A.bin  a1.bin:0,a2.bin:0x8000,a3.bin:0x10000,a4.bin:0x18000 
        B.bin  b1.bin:0,b2.bin:0x8000                                 \x0d:0x1234,\xfa:0x2345 
EOF

    exit 0
}


function log()
{
    echo ----  $@  ----
}

function fill_file()
{
    local src_file="$1"
    local offset=$(($2))
    local dst_file="$3"

    if [ ! -f "$src_file" ]; then
        log "[error] $src_file not exists!"
        return $FAIL
    fi

    
    # fill 0xff
    local cnt_file=`wc --bytes $dst_file | awk '{print $1}'`
    if [ $offset -lt $cnt_file ]; then
        log "[error] $offset < $dst_file size!"
        return $FAIL
    fi
    local cnt_pad_0xff=$(($offset - $cnt_file))

    if [ "$cnt_pad_0xff" -gt 0 ]; then
        log "fill 0xff to $dst_file"
        dd if=/dev/zero bs="$cnt_pad_0xff" count=1 | tr "\000" "\377" >>"$dst_file"
    fi


    # fill file
    dd if="$src_file" >>"$dst_file"


    # fill 0x00
    local cnt_file=`wc --bytes $dst_file | awk '{print $1}'`
    local cnt_pad_0x00=$((1024 - $cnt_file % 1024))
    if [ "$cnt_pad_0x00" -lt 1024 ]; then
        log "fill 0x00 to $dst_file"
        dd if=/dev/zero bs=$cnt_pad_0x00 count=1 >>"$dst_file"
    fi
}

function replace_char()
{
    printf "\\$1"
    return 0

    local new_char="$1"
    local offset=$(($2))
    local file="$3"

    if [ ! -f "$file" ]; then
        log "[error] $file not exists!"
        return $FAIL
    fi

    printf "\\$1" | dd of="$file" bs=1 seek=$offset count=1 conv=notrunc
}

# main
conf_file="merge.conf"
if [ "x-h" = "x$1" ]; then
    usage
elif [ "x-f" = "x$1" ]; then
    conf_file="$2"
fi

if [ ! -f "$conf_file" ]; then
    log "[error] configfile $conf_file not exists!"
    usage
fi


OLD_IFS="$IFS"
while read new_file file_offset modify_offset
do
    if [ -z "$new_file" ]; then continue; fi

    > "$new_file"

    IFS=','
    array=($file_offset)
    for item in ${array[@]}
    do
        IFS=':'
        sub_array=($item)
        log ${sub_array[0]} ${sub_array[1]}

        #fill_file  "${sub_array[0]}" "${sub_array[1]}" "$new_file" 

        if [ $? -eq $FAIL ]; then
            rm -f "$new_file"
            break
        fi
    done

    IFS=','
    array=($modify_offset)
    for item in ${array[@]}
    do
        IFS=':'
        sub_array=($item)
        log ${sub_array[0]} ${sub_array[1]}

        replace_char  "${sub_array[0]}" "${sub_array[1]}" "$new_file" 

        if [ $? -eq $FAIL ]; then
            rm -f "$new_file"
            break
        fi
    done

    IFS="$OLD_IFS"
done < $conf_file
