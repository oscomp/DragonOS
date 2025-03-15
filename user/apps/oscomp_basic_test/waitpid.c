#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>
#include <assert.h>

int i = 1000;

void test_waitpid(void) {
    int cpid, wstatus;
    cpid = fork();
    assert(cpid != -1);  // 确保 fork 成功

    if (cpid == 0) {  // 子进程
        while (i--);  // 执行一些计算，模拟工作
        //sched_yield();  // 不一定需要此调用
        printf("This is child process\n");
        exit(3);  // 子进程退出，返回状态为 3
    } else {  // 父进程
        pid_t ret = waitpid(cpid, &wstatus, 0);
        assert(ret != -1);  // 确保 waitpid 成功
        
        if (ret == cpid) {
            if (WIFEXITED(wstatus)) {  // 确保子进程正常退出
                if (WEXITSTATUS(wstatus) == 3) {
                    printf("waitpid successfully.\nwstatus: %x\n", WEXITSTATUS(wstatus));
                } else {
                    printf("waitpid error: child exited with unexpected status: %d\n", WEXITSTATUS(wstatus));
                }
            } else {
                printf("waitpid error: child did not exit normally.\n");
            }
        } else {
            printf("waitpid error: ret != cpid\n");
        }
    }
}

int main(void) {
    test_waitpid();
    return 0;
}
