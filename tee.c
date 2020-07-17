
// Created by aatzmon on 7/12/20.
// mimics the shell tee command, with support to -a option flag
//

#include <sys/stat.h>
#include <fcntl.h>
#include "lib/tlpi_hdr.h"

#ifndef BUF_SIZE /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int _main3(int argc, char *argv[]) {
    int fileFd, openFlags, readBytes, optionFlag;
    mode_t filePerms;
    const char *fileName;
    char buf[BUF_SIZE];

    if (argc < 2 || (strcmp(argv[1],"--help") == 0))
        usageErr("%s [OPTION]... [FILE]...",argv[0]);
    /* Open file */
    fileName = argv[argc-1];
    openFlags = O_CREAT | O_WRONLY;
    // checking for flags
    if ((optionFlag = getopt(argc,argv,":a")) == 'a')
        openFlags = openFlags | O_APPEND;
    else
        openFlags = openFlags | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw */
    fileFd = open(fileName,openFlags,filePerms);
    if (fileFd == -1)
        errExit("opening file %s", argv[0]);
    /* Read from STDIN; write to STDOUT and file*/
    while ((readBytes = read(STDIN_FILENO,buf,BUF_SIZE)) > 0){
        if (write(STDOUT_FILENO, buf, readBytes) != readBytes)
            fatal("couldn't write whole buffer");
        if (write(fileFd, buf, readBytes) != readBytes)
            fatal("couldn't write whole buffer");
    }
    close(fileFd);
    exit(EXIT_SUCCESS);
}
