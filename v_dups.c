//
// Created by aatzmon on 7/13/20.
//

#include <fcntl.h>
#include <errno.h>
#include "v_dups.h"
#include "lib/tlpi_hdr.h"

/* Simulates dup using fcntl*/
int v_dup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, 0);
}

/* Simulates dup2 using fcntl */
int v_dup2(int oldfd, int newfd) {
    // check if oldfd is valid, and handle
    if (fcntl(oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }
    if (oldfd == newfd) return newfd; // same FD, NOOP
    // close newfd if exists
    if (fcntl(newfd, F_GETFL) != -1)
        if (close(newfd) == -1)
            errExit("close");
    return fcntl(oldfd, F_DUPFD, newfd);
}

