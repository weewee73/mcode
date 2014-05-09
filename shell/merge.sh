#/bin/bash

SUCC=0
FAIL=255 #return -- -1;Exit codes should be in the range 0-255.

function log()
{
    echo ----  $@  ----
}

function fill_file()
{
    local src_file="$1"
    local offset=$(($2))
    local dst_file="$3"

    if [ ! -f "$src_file" ]; then
        log "[error] $src_file not exists!"
        return $FAIL
    fi

    
    # fill 0xff
    local cnt_file=`wc --bytes $dst_file | awk '{print $1}'`
    if [ $offset -lt $cnt_file ]; then
        log "[error] $offset < $dst_file size!"
        return $FAIL
    fi
    local cnt_pad_0xff=$(($offset - $cnt_file))

    if [ "$cnt_pad_0xff" -gt 0 ]; then
        log "fill 0xff to $dst_file"
        dd if=/dev/zero bs="$cnt_pad_0xff" count=1 | tr "\000" "\377" >>"$dst_file"
    fi


    # fill file
    dd if="$src_file" >>"$dst_file"


    # fill 0x00
    local cnt_file=`wc --bytes $dst_file | awk '{print $1}'`
    local cnt_pad_0x00=$((1024 - $cnt_file % 1024))
    if [ "$cnt_pad_0x00" -lt 1024 ]; then
        log "fill 0x00 to $dst_file"
        dd if=/dev/zero bs=$cnt_pad_0x00 count=1 >>"$dst_file"
    fi
}

# new_file    file_01:of_01,file_02:of_02     x_01:of_01,x_02:of_02 
OLD_IFS="$IFS"
while read new_file file_offset modify_offset
do
    if [ -z "$new_file" ]; then continue; fi

    > "$new_file"
    IFS=','
    array=($file_offset)
    for item in ${array[@]}
    do
        IFS=':'
        sub_array=($item)
        log ${sub_array[1]} ${sub_array[1]}

        #fill_file  "${sub_array[0]}" "${sub_array[1]}" "$new_file" 

        if [ $? -eq $FAIL ]; then
            rm -f "$new_file"
            break
        fi
    done



    IFS="$OLD_IFS"
done < merge.conf

