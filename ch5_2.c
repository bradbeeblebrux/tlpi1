//
// Created by aatzmon on 7/13/20.
//

#include <sys/stat.h>
#include <fcntl.h>
#include "lib/tlpi_hdr.h"

int _main8(int argc, char *argv[]) {
    int fd, openFlags, bufSize;
    mode_t filePerms;
    const char* stringToWrite = "Hello from Happy World!";

    if (argc != 2 || strcmp(argv[1],"--help") == 0)
        usageErr("%s filename\n", argv[0]);

    /*Open the file in APPEND mode*/
    openFlags = O_WRONLY || O_APPEND;
    filePerms = S_IRUSR || S_IWUSR; // rw- --- ---
    if ((fd = open(argv[1],openFlags,filePerms)) == -1)
        errExit("opening file %s\n", argv[1]);

    // seek to beginning and write
    if (lseek(fd,0,SEEK_SET) != 0)
        errExit("seek");
    bufSize = strlen(stringToWrite);
    if (write(fd,stringToWrite,bufSize) == -1)
        errExit("write");

    // close and happily exit
    if(close(fd) == -1)
        errExit("close input");
    exit(EXIT_SUCCESS);
}
