#!/bin/bash

msg_cn="
              ֪ͨ
"

msg_en="
                            MESSAGE
  I apologize and regret for any inconvenience caused by my testing.
                                                        -- xx
"

notify_all(){
    while [[ : ]]
    do
        echo "$msg_en" "$msg_cn" | wall
        sleep 2
    done
}

notify_others()
{
    myself=$(grep `tty | cut -b 6-` <(w -sh) | awk '{print $3}')

    while [[ : ]]
    do
        ttys=`w -sh | awk -v ip="$myself" '$3!=ip {print $2}'`
        for tty in $ttys
        do
            # not surport chinese
            echo "$msg_en" | write root $tty
        done
        sleep 2
    done
}

if [[ "$1" == "-a" ]]; then
    notify_all
else
    notify_others
fi

