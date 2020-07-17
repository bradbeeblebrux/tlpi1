//
// Created by aatzmon on 7/13/20.
//

#include <sys/stat.h>
#include <fcntl.h>
#include "lib/tlpi_hdr.h"

int atomic_append(int argc, char *argv[]) {
    int fd, openFlags, numOfBytes;
    mode_t filePerms;
    const char* charToWrite = "X";
    Boolean shouldAppend = TRUE;


    if (argc < 3 || argc > 4 || strcmp(argv[1],"--help") == 0)
        usageErr("%s filename num_of_bytes [x]\n", argv[0]);
    // check if 'x' argument was provided & open file
    if (argc == 4 && argv[3][0] == 'x')
        shouldAppend = FALSE;
    openFlags = O_WRONLY | O_CREAT;
    if (shouldAppend) openFlags |= O_APPEND;
    filePerms = S_IRUSR | S_IWUSR; // rw- --- ---
    if ((fd = open(argv[1],openFlags,filePerms)) == -1)
        errExit("opening file %s\n", argv[1]);

    numOfBytes = getInt(argv[2],GN_ANY_BASE,"atomic_append");

    if (!shouldAppend)
        if (lseek(fd,0,SEEK_END) == -1) // non-atomically seek to end
            errExit("lseek");
    /* Write one-bit-at-time */
    for (int i = 0; i < numOfBytes; i++)
        if ((write(fd,charToWrite,1)) == -1)
            errExit("write");

    // close file and leave
    if(close(fd) == -1)
        errExit("close input");
    exit(EXIT_SUCCESS);
}
