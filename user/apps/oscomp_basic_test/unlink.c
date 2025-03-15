#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>  // 添加此头文件以支持 open() 和 O_* 标志

/* 测试 unlink
 * 测试通过，应有如下输出：
 * "  unlink success!"
 * 测试失败，应有如下输出：
 * "  unlink error!"
 */

int test_unlink()
{
    char *fname = "./test_unlink";
    int fd, ret;

    // 创建并打开文件
    fd = open(fname, O_CREAT | O_WRONLY, 0666);  // 使用 O_CREAT 而不是 O_CREATE，0666 是权限
    if (fd < 0) {
        perror("open failed");
        return -1;
    }
    close(fd);

    // 删除文件
    ret = unlink(fname);
    if (ret == 0) {
        // 试图重新打开文件，确保文件已删除
        fd = open(fname, O_RDONLY);
        if (fd < 0) {
            printf("  unlink success!\n");
        } else {
            printf("  unlink error!\n");
            close(fd);
        }
    } else {
        printf("  unlink error!\n");
    }

    return 0;
}

int main(void) {
    test_unlink();
    return 0;
}
