#!/bin/sh
server="10.101.0.209"
port=21
username=$1
password=$2
ftp -n <<!
open $server
user $username $password
close
quit
!
