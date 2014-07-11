/*

1. Advisory Locking

Advisory locking requires cooperation from the participating processes.
Suppose process “A” acquires an WRITE lock, and it started writing into the file,
    and process “B”, without trying to acquire a lock, it can open the file and write into it.
Here process “B” is the non-cooperating process.
If process “B”, tries to acquire a lock, then it means this process is co-operating to ensure the “serialization”.

Advisory locking will work, only if the participating process are cooperative.
Advisory locking sometimes also called as “unenforced” locking.

2. Mandatory Locking

Mandatory locking doesn’t require cooperation from the participating processes.
Mandatory locking causes the kernel to check every open, read, and write to verify that the calling process isn’t violating a lock on the given file.
More information about mandatory locking can be found at kernal.org(http://kernel.org/doc/Documentation/filesystems/mandatory-locking.txt)


Compile the program using gcc.
    # cc -o file_lock file_lock.c

Remount the root filesystem with “mand” option using the mount command as shown below.
This will enable mandatory locking at the file system level.
Note: You need to be root to execute the below command.
    # mount -oremount,mand /

Create 2 files named “advisory.txt” and “mandatory.txt” in the directory where the executable (file_lock) is located.
Enable the Set-Group-ID and disable the Group-Execute-Bit for “mandatory.txt” as follows
    # touch advisory.txt
    # touch mandatory.txt
    # chmod g+s,g-x mandatory.txt

Test Advisory Locking: Now execute the sample program with ‘advisory.txt’ as the argument.
    # ./file_lock advisory.txt
The program will wait to get input from the user. From another terminal, or console, try the following
    # ls >>advisory.txt
In the above example, ls command will write its output to advisory.txt file.
Even though we acquire a write lock, still some other process ( Non Cooperating ) can write into the file.
This is termed as “Advisory” locking.
    
Test Mandatory Locking: Once again execute the sample program with ‘mandatory.txt’ as the argument.
    # ./file_lock mandatory.txt
From another terminal or console, try the following:
    # ls >>mandatory.txt
In the above example, ls command will wait for the lock to be removed before writing its output to the mandatory.txt file.
It is still a non-cooperative process, but locking is achieved using mandatory locking.
*/

#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    int fd = open(argv[1], O_WRONLY);
    if(fd == -1) {
      printf("Unable to open the file\n");
      exit(1);
    }
    static struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLKW, &lock);
    printf("Return value of fcntl:%d\n",ret);
    if(ret==0) {
      while (1) {
        scanf("%c", NULL);
      }

    /* Release the lock.  */
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);

    close (fd);

    }
  }
}
