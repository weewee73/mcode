#!/bin/sh

alias ..="cd .."
alias ..2="cd ../.."
alias ..3="cd ../../.."
alias ..4="cd ../../../.."
alias ..5="cd ../../../../.."

alias lx='ls -lXB'         #  Sort by extension.
alias lk='ls -lSr'         #  Sort by size, biggest last.
alias lt='ls -lAtr'        #  Sort by date, most recent last.
alias lc='ls -ltcr'        #  Sort by/show change time,most recent last.
alias lu='ls -ltur'        #  Sort by/show access time,most recent last.

alias grep='grep --color=auto'
alias mdate='date "+%Y-%m-%d %T"'
alias tmux='TERM=xterm-256color tmux'
alias cvs_status='cvs status | grep -v "^ " | grep -v "^$" | grep -v = | grep -v "Status: Up-to-date"'
alias mfind_ch="find . -regex '.*\.\(c\|cpp\|h\)$' -print | xargs grep --color=auto -n "
alias mfind_lua='find . -name "*.lua" -print | xargs grep --color=auto -n '
alias vi='vim'
alias psgrep='ps aux | grep '


#set -e
#set -u

calc() { echo "$*" | bc -l; }
mkdircd() { mkdir -p "$@" && eval cd "\"\$$#\""; }
#mfind_ch() { find . -regex '.*\.\(c\|cpp\|h\)$' -print | xargs grep --color=auto -n $@ ; }
#mfind_lua() { find . -name "*.lua" -print | xargs grep --color=auto -n $@ ; }
mtail() { tail -n +"$2" $1 | head -n $3; }
mcount() { grep -o "$1" $2 | sort -n | uniq -c | sort -nr; }

# Find a file with a pattern in name:
ff() { find . -type f -iname '*'"$*"'*' -ls | column -t ; }
# Find a file with pattern $1 in name and Execute $2 on it:
fe() { find . -type f -iname '*'"${1:-}"'*' -exec ${2:-file} {} \;  ; }

cp936_to_utf8() { iconv -f cp936 -t utf8 -o $1.tmp $1 && mv -i $1 $1.original && mv -i $1.tmp $1; }
utf8_to_cp936() { iconv -t cp936 -f utf8 -o $1.tmp $1 && mv -i $1 $1.original && mv -i $1.tmp $1; }

value_to_hex() { local value=$1; if [ -z "$value" ]; then read value; fi; printf "0x%x\n" $(($value)); }
value_to_oct() { local value=$1; if [ -z "$value" ]; then read value; fi; printf "0%o\n"  $(($value)); }
value_to_dec() { local value=$1; if [ -z "$value" ]; then read value; fi; echo $(($value)); }
value_to_bin() { local value=$1; if [ -z "$value" ]; then read value; fi; echo "obase=2;ibase=10;$(($value))" | bc; }
bin_to_value() { local value=$1; if [ -z "$value" ]; then read value; fi; echo "obase=10;ibase=2;$value" | bc; }
bin_to_value2() { local value=$1; if [ -z "$value" ]; then read value; fi; echo $((2#$value)); }

my_ip() {
    MY_IP=$(/sbin/ifconfig eth0 | awk '/inet/ { print $2 } ' | sed -e s/addr://)
    echo ${MY_IP:-"Not connected"}
}

repeat() {
    local i max
    max=$1; shift;
    for ((i=1; i <= max ; i++))
    do
        eval "$@";
    done
}

ask() {
    #if ask "Kill process $pid <$pname> with signal $sig?"
    #then kill $sig $pid
    #fi
    echo -n "$@" '[y/n] ' ; read ans
    case "$ans" in
        y*|Y*) return 0 ;;
        *) return 1 ;;
    esac
}

corefile_name() {
    for file ; do
        echo -n $file : ; gdb --core=$file --batch | head -2
    done
}

random() {
    X=${1:-100}
    N=${2:-10}
    while [ "$N" -gt 0 ]
    do
        echo -ne "$[RANDOM%X+1] "
        N=$[N-1]
    done
    echo
}


# Create a backup of the given file(s)
# USAGE: bak file1 file2 file3
#        -> result: file1.bak file2.bak file3.bak
bak() {
    local file

    for file in "$@"
    do
        cp $file{,.bak}
    done
}

# Restores the file from backup
# USAGE: rbak file.bak
#        -> result: replaces file.bak with file
rbak() {
    local file
    local file_bak

    for file_bak in "$@"
    do
        if [[ $file_bak == *.bak ]]; then
            file=${file_bak:0:$((${#file_bak}-4))}
        else
            echo "$1 is not backup file!"
            continue
        fi

        read -p "Replace [$file_bak] with [$file] ? (y/N) " -n 2 REPLY
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            `cp $file_bak $file`
        fi
    done

}

# Handy Extract Program
extract() {
    if [ -f $1 ] ; then
        case $1 in
            *.tar.bz2)   tar xvjf $1     ;;
            *.tar.gz)    tar xvzf $1     ;;
            *.tar.xz)    tar xvJf $1     ;;
            *.bz2)       bunzip2 $1      ;;
            *.rar)       unrar x $1      ;;
            *.gz)        gunzip $1       ;;
            *.tar)       tar xvf $1      ;;
            *.tbz2)      tar xvjf $1     ;;
            *.tgz)       tar xvzf $1     ;;
            *.zip)       unzip $1        ;;
            *.Z)         uncompress $1   ;;
            *.7z)        7z x $1         ;;
            *)           echo "'$1' cannot be extracted via >extract<" ;;
        esac
    else
        echo "'$1' is not a valid file!"
    fi
}
#complete -f -o default -X '!*.+(zip|ZIP|z|Z|gz|GZ|bz2|BZ2)' extract



# four functions: mark, markcd, markrm, marks
#
# mark xxx  : adds sym link xxx to current dir to $MARKPATH
# marks     : list all marks
# markcd xxx: cd to the dir referred to as xxx
# markrm xxx: remove sym link xxx
export MARKPATH=$HOME/.marks
function mark() { 
    mkdir -p $MARKPATH; ln -s $(pwd) $MARKPATH/$1
}
function marks {
    ls -l $MARKPATH | sed 's/  / /g' | cut -d' ' -f9- | sed 's/ -/\t-/g' && echo
}
function markrm() { 
    local del_links

    if [ "$1" = "-a" ]; then
        rm $MARKPATH/*
        return 0
    fi

    for link in ${@}
    do
        del_links=$del_links" $MARKPATH/$link"
    done

    rm -i $del_links
}
function markcd() {
    if [ -z "$1" ]; then
        ls -l $MARKPATH | sed 's/  / /g' | cut -d' ' -f9-
        return 0
    fi

    cd -P $MARKPATH/$1 2>/dev/null || echo "No such mark: $1"
}
# Completion using available marks
# http://stackoverflow.com/questions/803653/bash-completion-for-certain-types-of-files-in-a-special-directory
function _marks_show() {
    local cur=${COMP_WORDS[COMP_CWORD]}
    local marks=$(find $MARKPATH -type l -printf "%f\n")
    COMPREPLY=($( compgen -W "${marks[@]}" -- "$cur" ) )
}
complete -o default -o nospace -F _marks_show cdmark
complete -o default -o nospace -F _marks_show markcd
complete -o default -o nospace -F _marks_show markrm
alias cdmark=markcd



function check_command() {
  CMD=`which $1` > /dev/null 2>&1
  if [ $? -ne 0 ] ; then
     echo "[CRIT] Command $1 not found. Cannot continue."
     exit 1
  fi
  _RET=${CMD}
  return 0
}
#check_command grep; grepcmd=${_RET}

