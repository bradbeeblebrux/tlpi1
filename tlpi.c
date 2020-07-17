//
// Created by aatzmon on 7/13/20.
//
#include "atomic_append.h"
#include "lib/tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include "v_dups.h"


int main(int argc, char *argv[]) {
    extern char etext, edata, end;
    struct mallinfo t_mal;

    printf("My proces id is %d, My parent process id is %d\n",getpid(), getppid());
    printf("%p %p %p\n",&etext, &edata, &end);
    t_mal = mallinfo();
    exit(EXIT_SUCCESS);
}
