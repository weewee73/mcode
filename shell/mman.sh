#!/bin/bash

name=${!#}
#name=${@:$#}
#name=${@: -1}

f_man="$HOME/github/mcode/doc/$name.man"
if [[ $# -eq 2 ]]; then
    section=$1
    f_man="$HOME/github/mcode/doc/${name}_${section}.man"
fi


if [ ! -e $f_man ]; then
    man $section $name >/dev/null
    ret=$?
    if [ $ret -ne 0 ]
    then
        exit $ret
    fi
    section="-a"
    man $section $name | col -bx | sed "s/\xe2\x80\x98/'/g" | sed "s/\xe2\x80\x99/'/g" | sed 's/\(\w\+\)\s\{2,3\}\(\w\+\)\(\s\)*/\1 \2\3/g' >$f_man
fi

vim $f_man
