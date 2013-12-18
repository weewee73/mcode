#!/bin/bash

f_config="/etc/ntp.conf"

config()
{
    echo "config.."
    cat >$f_config <<EOF
#restrict 192.168.60.129
#restrict 127.0.0.1 
#restrict -6 ::1
#restrict 192.168.2.0 mask 255.255.255.0

#permit all
restrict default

server time.nist.gov prefer

#local clock
server 127.127.1.0 
fudge 127.127.1.0 stratum 8

driftfile /etc/ntp.drift
EOF
	RET=$?
    return $RET

}

#set time zone
\cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

#set firewall
iptables -D INPUT -p udp --dport 123 -j ACCEPT
iptables -I INPUT -p udp --dport 123 -j ACCEPT
/etc/rc.d/init.d/iptables save <<EOF
y
EOF

config
