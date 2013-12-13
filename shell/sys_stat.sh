#/bin/bash

count=5
cnt=$(($count+1))

#top -bM -n 2 -d 1 | grep "^[CM]" | tail -n 2
# USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND

f_ps="/tmp/ps.log"
#                    PID CPU MEM RSS VSZ COMMAND
ps aux | awk '{print $2, $3, $4, $6, $5, $11}'>$f_ps
awk 'NR!=1 {cpu+=$2; mem+=$3; rss+=$4; vsz+=$5} END {print "\n""CPU:"cpu"%  ""MEM:"mem"%  ""MEM(RSS):"rss"k  ""MEM(VSZ):"vsz"K"}' $f_ps

echo -e "\nCPU TOP $count:"
sort -r -k2 $f_ps | head -n $cnt | column -t

echo -e "\nMEM TOP $count:"
sort -r -k3 $f_ps | head -n $cnt | column -t


dir=`pwd`
cd $dir
echo -e "\nDIRECTORY SPACE USAGE:"
du -sh *


echo -e "\nOPEN FILE TOP $count:"
echo  "CNT NAME PID" | column -t
lsof | awk '{print $1,$2}' | uniq -c | sort -nr | head -n $cnt | column -t


#dir="/icooper/log"
#size="20M"
dir=`pwd`
size="10k"
echo -en "\n$dir has `ls -a $dir | wc -l` files\n"
echo -en "file size is more than $size:\n`find $dir -maxdepth 1 -size +${size} | xargs du -sh `\n"

