#!/bin/bash

name=${!#}
#name=${@:$#}
#name=${@: -1}

f_man="$HOME/github/mcode/doc/$name.man"

if [ ! -e $f_man ]
then
    man $name >/dev/null
    ret=$?
    if [ $ret -ne 0 ]
    then
        exit $ret
    fi
    man $name | col -bx | sed "s/\xe2\x80\x98/'/g" | sed "s/\xe2\x80\x99/'/g" | sed 's/\(\w\+\)\s\{2,3\}\(\w\+\)\s*/\1 \2 /g' >$f_man
fi

vim $f_man
