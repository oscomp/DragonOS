#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/wait.h>  // 需要包含此头文件
#include <assert.h>

void test_wait(void) {
    int cpid, wstatus;
    cpid = fork();
    
    if (cpid == 0) {
        // 子进程执行代码
        printf("This is child process\n");
        exit(0);  // 子进程正常退出
    } else {
        // 父进程等待子进程退出
        pid_t ret = wait(&wstatus);
        assert(ret != -1);
        
        if (ret == cpid) {
            printf("wait child success.\n");
            
            // 检查子进程是否正常退出
            if (WIFEXITED(wstatus)) {
                printf("Child exited with status: %d\n", WEXITSTATUS(wstatus));
            } else {
                printf("Child process did not exit normally.\n");
            }
        } else {
            printf("wait child error.\n");
        }
    }
}

int main(void) {
    test_wait();
    return 0;
}
