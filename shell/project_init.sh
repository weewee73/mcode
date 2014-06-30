#!/bin/bash

find .  -name "*.[ch]" >cscope.files

cscope -bq
ctags --sort=yes --c-kinds=+px -L cscope.files

awk -v fcolor="c.vim" '
BEGIN{
    Tenum="syn keyword cEnum "
    Ttypedef="syn keyword cType "
    Tdefine="syn keyword cDefine "
    Tglobal="syn keyword cGlobalVal "
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
}
END{
    if (length(Tenum) > length("syn keyword cEnum "))
        print Tenum >fcolor
        print "hi cEnum ctermfg=DarkRed" >> fcolor
    if (length(Ttypedef) > length("syn keyword cType "))
        print Ttypedef >>fcolor
    if (length(Tenum) > length("syn keyword cDefine "))
        print Tdefine >>fcolor
    if (length(Tenum) > length("syn keyword cGlobalVal "))
        print Tglobal >>fcolor
        print "hi def link cGlobalVal cDefine" >> fcolor
}
' tags

[ -e ~/.vim/syntax ] || mkdir -p ~/.vim/syntax
if [ -f ~/.vim/syntax/common.vim ]; then
    cat c.vim "$HOME/.vim/syntax/common.vim" >"$HOME/.vim/syntax/c.vim"
else
    cp c.vim "$HOME/.vim/syntax/c.vim"
fi

