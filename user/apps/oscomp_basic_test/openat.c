#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>   // 需要包含 fcntl.h 以声明 openat 和 O_CREAT
#include <string.h>   // 用于 strlen
#include <assert.h>

void test_openat(void) {
    // TEST_START(__func__);
    int fd_dir = open("./mnt", O_DIRECTORY);  // 打开目录
    printf("open dir fd: %d\n", fd_dir);
    
    // 使用 openat 来相对目录描述符打开文件
    int fd = openat(fd_dir, "test_openat.txt", O_CREAT | O_RDWR, 0666);  // O_CREAT 和 O_RDWR 必须指定权限
    printf("openat fd: %d\n", fd);
    
    assert(fd > 0);
    printf("openat success.\n");

    // 可选代码：向文件中写入数据
    char buf[256] = "openat text file";
    write(fd, buf, strlen(buf));
    
    // 读取数据并验证
    int size = read(fd, buf, 256);
    if (size > 0) {
        printf("Read success: %s\n", buf);
    } else {
        printf("Read error.\n");
    }

    close(fd);
    close(fd_dir);  // 记得关闭目录文件描述符
    // TEST_END(__func__);
}

int main(void) {
    test_openat();
    return 0;
}
