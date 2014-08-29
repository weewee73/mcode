
#atomic operation avoid RaceCondition

#NFSv2 has two atomic operations:
    #symlink
    #rename
#With NFSv3 the create call is also atomic.
#Directory operations are NOT atomic under NFSv2 and NFSv3
#(please refer to the book 'NFS Illustrated' by Brent Callaghan, ISBN 0-201-32570-5; Brent is a NFS-veteran at Sun).

################################# dir lock #########################################
lockdir=/tmp/dir.lock
if mkdir "$lockdir" ; then
    echo >&2 "successfully acquired lock"

    # Remove lockdir when the script finishes, or when it receives a signal
    trap 'rm -rf "$lockdir"' 0

    # Optionally create temporary files in this directory, because
    # they will be removed automatically:
    tmpfile=$lockdir/filelist

else
    echo >&2 "cannot acquire lock, giving up on $lockdir"
    exit 0
fi

sleep 99999

################################### fd lock #######################################
lockdir=/tmp/dir.lock

exec 9>/tmp/lock.file
if ! flock -n 9  ; then
    echo "another instance is running";
    exit 1
fi
# this now runs under the lock until 9 is closed (it will be closed automatically when the script ends)
sleep 99999


#       mutex file
#
# Open a mutual exclusion lock on the file, unless another process already owns one.
#
# If the file is already locked by another process, the operation fails.
# This function defines a lock on a file as having a file descriptor open to the file.
# This function uses FD 9 to open a lock on the file.
# To release the lock, close FD 9:  exec 9>&-
#
mutex() {
    local file=$1 pid pids 

    # trouble, child process whill inherit FD 9
    exec 9>>"$file"

    { pids=$(fuser -f "$file"); } 2>&- 9>&- 

    for pid in $pids; do
        [[ $pid = $$ ]] && continue

        exec 9>&- 
        return 1 # Locked by a pid.
    done 
} 

mutex /var/run/myscript.lock || { echo "Already running." >&2; exit 1; }




mutex_pgrep() {
    local pid pids 

    pids=$(pgrep `basename $0`)

    for pid in $pids; do
        [[ $pid -eq $$ ]] && continue

        return 1
    done 
} 

mutex_pgrep || { echo "Already running." >&2; exit 1; } 
