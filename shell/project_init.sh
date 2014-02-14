#ctags -R --c-kinds=+px
#cscope -Rbq

#cflow file in top dir
#find . -name "*.c" | 
#    while read cfile
#    do 
#        cflowfile=`echo $cfile | sed 's#/#_#g'`; 
#        cflow $cfile -o ${cflowfile}.cflow; 
#    done

#find . -name "*.c" | tee c.file | xargs -I{} cflow {} -o {}.cflow
#cat c.file | xargs cflow  -o all.cflow


source=`pwd`

echo -ne "\033]0;$(basename $source) coding...\007"

ctags -R --c-kinds=+px
cscope -Rbq

f_session="Session.vim"
if [[ -f $f_session ]]; then
#    vim -c "cs add $source/cscope.out $source" -S $f_session
    vim -S $f_session
else
#    vim -c "cs add $source/cscope.out $source" .
    vim $source
fi

