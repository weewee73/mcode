#!/bin/bash

mkdir -p $HOME/.vim/syntax
f_color="$HOME/.vim/syntax/lua.vim"

find . -name "*.lua" -print >cscope.files

cscope -bq

ctags --sort=yes --excmd=number -L cscope.files \
        --langdef=MYLUA \
        --langmap=MYLUA:.lua \
        --regex-MYLUA="/^.*\s*function\s*(\w+):(\w+).*$/\2/f/" \
        --regex-MYLUA="/^.*\s*function\s*(\w+)\.(\w+).*$/\2/f/" \
        --regex-MYLUA="/^.*\s*function\s*(\w+)\s*\(.*$/\1/f/" \
        --regex-MYLUA="/^\s*(\w+)\s*=\s*\{.*$/\1/e/" \
        --regex-MYLUA="/^\s*(\w+)\s*=\s*[0-9]+.*$/\1/e/" \
        --regex-MYLUA="/^\s*module\s+\"(\w+)\".*$/\1/m,module/" \
        --regex-MYLUA="/^\s*module\s+\"[a-zA-Z0-9._]+\.(\w+)\".*$/\1/m,module/" \
        --languages=MYLUA

CustomFunc='
syn match    cCustomParen    "(" contains=cParen
syn match    cCustomFunc     "\w\+\s*(" contains=cCustomParen
hi cCustomFunc ctermfg=blue
'
echo "$CustomFunc" >$f_color

awk -v fcolor="$f_color" '
BEGIN{
    Tenum="syn keyword cEnum "
    Ttypedef="syn keyword cType "
    Tdefine="syn keyword cDefine "
    Tglobal="syn keyword cGlobalVal "
    Tfunction="syn keyword cFunction "
}
{
    if (/;"\te/)
        Tenum = Tenum " " $1
    else if (/;"\tt/)
        Ttypedef  = Ttypedef " " $1
    else if (/;"\td/)
        Tdefine  = Tdefine " " $1
    else if (/;"\tv/)
        Tglobal  = Tglobal " " $1
    else if (/;"\tf/)
        Tfunction = Tfunction "  " $1
}
END{
    if (length(Tenum) > length("syn keyword cEnum "))
        print Tenum >>fcolor
        print "hi cEnum ctermfg=DarkRed" >> fcolor
    if (length(Ttypedef) > length("syn keyword cType "))
        print Ttypedef >>fcolor
    if (length(Tdefine) > length("syn keyword cDefine "))
        print Tdefine >>fcolor
    if (length(Tglobal) > length("syn keyword cGlobalVal "))
        print Tglobal >>fcolor
        print "hi def link cGlobalVal cDefine" >> fcolor
    if (length(Tfunction) > length("syn keyword cFunction "))
        print Tfunction >>fcolor
        print "hi cFunction cterm=bold ctermfg=blue" >> fcolor
}
' tags

if [ -f ~/.vim/syntax/common.vim ]; then
    cat "$HOME/.vim/syntax/common.vim" >>$f_color
fi

