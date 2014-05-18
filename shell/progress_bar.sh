#!/bin/bash 

#puts the cursor at line L and column C.
# \033[<L>;<C>H Or \033[<L>;<C>f
#
#Move the cursor up N lines:
# \033[<N>A
#
#Move the cursor down N lines:
# \033[<N>B
#
#Move the cursor forward N columns:
# \033[<N>C
#
#Move the cursor backward N columns:
# \033[<N>D
#
#Clear the screen, move to (0,0):
# \033[2J
#
#Erase to end of line:
# \033[K
#
#Save cursor position:
# \033[s
#
#Restore cursor position:
# \033[u

i=0
while [ $i -lt 10 ] 
do 
    ((i++)) 
    echo -ne "=>\033[s" 
    echo -ne "\033[40;50H"$((i*5*100/100))%"\033[u\033[1D" 

    sleep 0.1
done 
echo 



b='>'
max=100
for ((i=0; i<max; i++)) 
do 
    printf "%3d%%: [%-${max}s]\r" $i $b 
    sleep 0.1 
    b="=$b" 
done 
echo 


b="/"
for((i=0; i<40; i++))
do
    printf "please wait %s \r" $b
    sleep 0.1
    let "c=$i % 4"
    case $c in
        0) b="/";;
        1) b="-";;
        2) b="\\";;
        3) b="|";;
esac
done
echo


i=0
while [ $i -lt 10 ]
do
    for j in '-' '\\' '|' '/'
    do
        echo -ne "\033[1D$j"
        sleep 0.1 
    done
    ((i++))
done
