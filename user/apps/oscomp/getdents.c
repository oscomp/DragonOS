#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <assert.h>
#include <stdint.h>

// linux_dirent64 定义
struct linux_dirent64 {
    uint64_t        d_ino;
    int64_t         d_off;
    unsigned short  d_reclen;
    unsigned char   d_type;
    char            d_name[];
};

char buf[512];
void test_getdents(void){
    int fd, nread;
    struct linux_dirent64 *d;
    int bpos;

    fd = open(".", O_RDONLY | O_DIRECTORY);
    assert(fd >= 0);
    printf("open fd: %d\n", fd);

    nread = syscall(SYS_getdents64, fd, buf, sizeof(buf));
    printf("getdents read bytes: %d\n", nread);
    assert(nread != -1);

    for (bpos = 0; bpos < nread; ) {
        d = (struct linux_dirent64 *)(buf + bpos);
        printf("%s\t", d->d_name);
        bpos += d->d_reclen;
    }

    printf("\n");
    close(fd);
}

int main(void){
    test_getdents();
    return 0;
}
