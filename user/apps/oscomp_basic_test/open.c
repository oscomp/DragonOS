#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <fcntl.h>  // 需要包含 fcntl.h 来声明 open

void test_open() {
    // TEST_START(__func__);
    // O_RDONLY = 0, O_WRONLY = 1
    int fd = open("./text.txt", O_RDONLY);  // O_RDONLY 表示以只读模式打开文件
    assert(fd >= 0);
    
    char buf[256];
    int size = read(fd, buf, 256);
    if (size < 0) {
        size = 0;
    }
    write(STDOUT_FILENO, buf, size);  // 使用 STDOUT_FILENO 代替 STDOUT
    close(fd);
    // TEST_END(__func__);
}

int main(void) {
    test_open();
    return 0;
}
