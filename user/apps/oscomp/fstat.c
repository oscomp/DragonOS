#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h> 

#define AT_FDCWD (-100) //相对路径

//Stat *kst;
void test_fstat() {
    int fd = open("./text.txt", O_RDONLY);
    assert(fd >= 0);

    struct stat st;
    int ret = fstat(fd, &st);
    printf("fstat ret: %d\n", ret);
    assert(ret >= 0);

    printf("fstat: dev: %ld, inode: %ld, mode: %o, nlink: %ld, size: %ld, atime: %ld, mtime: %ld, ctime: %ld\n",
        st.st_dev, st.st_ino, st.st_mode, st.st_nlink,
        st.st_size, st.st_atime, st.st_mtime, st.st_ctime);

    close(fd);
}

int main(void) {
    test_fstat();
    return 0;
}
