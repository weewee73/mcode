#!/bin/bash

NO_ARGS=0
E_OPTERROR=85

if [ $# -eq "$NO_ARGS" ]
then
	echo "Usage: `basename $0` options (-mnopqrs)"
	exit $E_OPTERROR
fi

set -- `getopt "abcd:" "$@"`

while [ ! -z "$1" ]
do
	case "$1" in
		-a) echo "Option \"a\"";;
		-b) echo "Option \"b\"";;
		-c) echo "Option \"c\"";;
		-d) echo "Option \"d\" $2";;
		 *) break;;
	 esac

	 shift
done

exit 0

while getopts ":mnopq:rs" Option
do
	case $Option in
		m 	) 	echo "Scenario #1: option -$Option- [OPTIND=${OPTIND}]";;
		n|o ) 	echo "Scenario #2: option -$Option- [OPTIND=${OPTIND}]";;
		p 	) 	echo "Scenario #3: option -$Option- [OPTIND=${OPTIND}]";;
		q 	) 	echo "Scenario #4: option -$Option- with argument ${OPTARG} [OPTIND=${OPTIND}]";;
		r|s ) 	echo "Scenario #5: option -$Option- [OPTIND=${OPTIND}]";;
		*	) 	echo "Unimplemented option chosen -$Option- [OPTIND=${OPTIND}].";;
	esac
done

shift $(($OPTIND - 1))

exit $?
