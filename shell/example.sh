#!/usr/bin/env bash

VERSION=0.0.1

NO_ARGS=0
E_OPTERROR=85
E_SUCC=0
E_FAIL=255

g_variable=0


Usage() {

cat <<EOF
Usage: `basename $0` [OPTION]

    -v
        show version.
EOF

}

Func1() {
    local var1
    : 
}

Func2() {
    local var1
    : 
}


Main(){

    if [ $# -eq "$NO_ARGS" ]; then 
        Usage
        exit $E_OPTERROR
    fi

    while getopts "a:bcv" option
    do
        case $option in
            a)
                Func1 "${OPTARG}"
                ;;
            b|c)
                Func2
                ;;
            v)
                echo `basename $0` ver$VERSION
                exit 0
                ;;
        esac
    done
    shift $(($OPTIND - 1))

}


Main ${@}
