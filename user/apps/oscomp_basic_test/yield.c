#include <sched.h> // Include this header for sched_yield()
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


/*
理想结果：三个子进程交替输出
*/

void test_yield() {
    // TEST_START(__func__);

    for (int i = 0; i < 3; ++i) {
        if (fork() == 0) {
            for (int j = 0; j < 5; ++j) {
                sched_yield();
                printf("  I am child process: %d. iteration %d.\n",
                       getpid(),
                       i);
            }
            exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    // TEST_END(__func__);
}

int main(void) {
    test_yield();
    return 0;
}