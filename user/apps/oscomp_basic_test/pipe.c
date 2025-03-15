#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/wait.h"  // 包含 wait 函数
#include <assert.h>

/*
 * 成功测试时的输出：
 * "  Write to pipe successfully."
 */
static int fd[2];

void test_pipe(void) {
    int cpid;
    char buf[128] = {0};
    int ret = pipe(fd);
    assert(ret != -1);  // 创建管道

    const char *data = "  Write to pipe successfully.\n";
    cpid = fork();  // 创建子进程
    printf("cpid: %d\n", cpid);

    if (cpid > 0) {  // 父进程
        close(fd[1]);  // 关闭写端
        while (read(fd[0], buf, 1) > 0)  // 从管道读取数据
            write(STDOUT_FILENO, buf, 1);  // 写到标准输出
        write(STDOUT_FILENO, "\n", 1);  // 输出换行
        close(fd[0]);
        wait(NULL);  // 等待子进程结束
    } else {  // 子进程
        close(fd[0]);  // 关闭读端
        write(fd[1], data, strlen(data));  // 向管道写入数据
        close(fd[1]);
        exit(0);  // 子进程退出
    }
}

int main(void) {
    test_pipe();  // 调用管道测试
    return 0;
}
