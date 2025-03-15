#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>  // 包含 mkdir
#include <fcntl.h>     // 包含 open
#include <assert.h>

void test_mkdir(void) {
    int rt, fd;

    rt = mkdir("test_mkdir", 0666);  // 创建目录，权限为 0666
    printf("mkdir ret: %d\n", rt);
    assert(rt != -1);  // 如果 mkdir 返回 -1，表示出错

    fd = open("test_mkdir", O_RDONLY | O_DIRECTORY);  // 打开目录
    if (fd > 0) {
        printf("mkdir success.\n");
        close(fd);  // 关闭文件描述符
    } else {
        printf("mkdir error.\n");
    }
}

int main(void) {
    test_mkdir();  // 测试 mkdir 函数
    return 0;
}
