ctags -R --c-kinds=+px
cscope -Rbq

#cflow file in top dir
#find . -name "*.c" | 
#    while read cfile
#    do 
#        cflowfile=`echo $cfile | sed 's#/#_#g'`; 
#        cflow $cfile -o ${cflowfile}.cflow; 
#    done

find . -name "*.c" | tee c.file | xargs -I{} cflow {} -o {}.cflow
cat c.file | xargs cflow  -o all.cflow
