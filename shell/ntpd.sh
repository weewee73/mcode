#!/bin/bash

f_config="/etc/ntp.conf"
prog="/usr/local/bin/ntpd"

start() 
{
	[ -x $prog ] || exit 1
	[ -f $f_config ] || exit 2

	echo -n $"Starting ntp: "
	$prog -g -c $f_config
	RET=$?
	echo

	return $RET
}

stop() 
{
    echo -n $"Shutting down ntp: "
	pkill ntp 2>/dev/null
	RET=$?
    echo

	return $RET
}



case "$1" in
  start)
	start
	;;
  stop)
	stop
	;;
  restart)
	stop
	start
	;;
  *)
	echo $"Usage: $0 {start|stop|restart}" 
	exit 3
esac
