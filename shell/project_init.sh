#!/bin/bash

find .  -name "*.[ch]" >cscope.files

cscope -bq
ctags --sort=yes --c-kinds=+px -L cscope.files

CustomFunc='
syn match    cCustomParen    "(" contains=cParen
syn match    cCustomFunc     "\w\+\s*(" contains=cCustomParen
hi cCustomFunc ctermfg=blue
'
echo "$CustomFunc" >c.vim

awk -v fcolor="c.vim" '
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
    if (length(Tenum) > length("syn keyword cDefine "))
        print Tdefine >>fcolor
    if (length(Tenum) > length("syn keyword cGlobalVal "))
        print Tglobal >>fcolor
        print "hi def link cGlobalVal cDefine" >> fcolor
    if (length(Tfunction) > length("syn keyword cFunction "))
        print Tfunction >>fcolor
        print "hi cFunction cterm=bold ctermfg=blue" >> fcolor
}
' tags

[ -e ~/.vim/syntax ] || mkdir -p ~/.vim/syntax
if [ -f ~/.vim/syntax/common.vim ]; then
    cat c.vim "$HOME/.vim/syntax/common.vim" >"$HOME/.vim/syntax/c.vim"
else
    cp c.vim "$HOME/.vim/syntax/c.vim"
fi

