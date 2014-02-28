#!/bin/bash

f_word_xml="$HOME/github/mcode/shell/word.xml"
f_words="$f_word_xml.list~"
f_word_history="$f_word_xml.history~"

if [ ! -f "$f_word_xml" ]; then
	echo "error! no $f_word_xml!"	
	exit 1
fi

if [ "-topx" = "$1x" ]; then
	#history words statistic
	number=40
	if [ -n "$2" ]; then
		number=$2
	fi
	awk -F ',' '{print $1}' $f_word_history | sort | uniq -c | sort -nr |  head -n $number
	
elif [ -n "$1" ]; then
	#query word
	#rm -f /usr/bin/mword && ln -s $HOME/github/mcode/shell/mword.sh /usr/bin/mword
	word="$1"
	sed -n "/<word>$word/,/<\/trans>/p" $f_word_xml | xargs echo | sed 's/.*CDATA\[\(.*\)\]\]><\/trans>/\1/g'

	echo "$word,`date +"%Y/%m/%d %H:%M:%S"`" >>$f_word_history

else
	#prompt word
	#add PROMPT_COMMAND to ~/.bashrc
	#PROMPT_COMMAND='$HOME/github/mcode/shell/mword.sh'

	start_time=1389534029
	step_time=1
	day_count=20

	pass_time=$((`date +%s`-$start_time))

	today_base=`echo "$pass_time/86400*$day_count + 1" | bc`
	count=`echo "$today_base + $pass_time/$step_time%$day_count" | bc`

	if [ ! -f "$f_words" ]; then
		grep '<word>' $f_word_xml | sed 's/.*<word>\(.*\)<\/word>.*/\1/g' >$f_words
	fi

	word=`sed -n "$count p" $f_words`

	#echo -ne "\n\e[1;35m[$count: $word]\e[m\n"

	#set window's title
	#echo -ne "\033]0;$word ---- $USER@$HOSTNAME: $PWD\007"
	echo -ne "\033]0;$word\007"

fi
