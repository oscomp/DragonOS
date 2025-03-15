#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"  // 包含 open() 需要的头文件

void test_read() {
    // TEST_START(__func__);

    // 使用 O_RDONLY 打开文件
    int fd = open("./text.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;  // 文件打开失败则返回
    }

    char buf[256];
    int size = read(fd, buf, sizeof(buf));
    if (size < 0) {
        perror("read");
        close(fd);
        return;  // 读取失败则返回
    }

    write(STDOUT_FILENO, buf, size);  // 使用 STDOUT_FILENO 写入标准输出
    close(fd);  // 关闭文件描述符

    // TEST_END(__func__);
}

int main(void) {
    test_read();
    return 0;
}
