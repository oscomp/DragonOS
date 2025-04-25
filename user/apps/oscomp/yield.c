#include <sched.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

/*
理想结果：三个子进程交替输出
*/

int test_yield(){

    for (int i = 0; i < 3; ++i){
        if(fork() == 0){
	    for (int j = 0; j< 5; ++j){
                sched_yield();
                printf("  I am child process: %d. iteration %d.\n", getpid(), i);
	    }
	    exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}

int main(void) {
    test_yield();
    return 0;
}
