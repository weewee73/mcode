#!/bin/bash

name=$_
f_man="$HOME/github/mcode/doc/$name.man"

if [ ! -e $f_man ]
then
    man $name >/dev/null
    ret=$?
    if [ $ret -ne 0 ]
    then
        exit $ret
    fi
    man $name | col -b >$f_man
fi

vim $f_man
