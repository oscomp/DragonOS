#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <assert.h>

#define STACK_SIZE (1024 * 1024)

static int child_func(void *arg){
    printf("  Child says successfully!\n");
    return 0;
}

void test_clone(void){
    void *stack = malloc(STACK_SIZE);
    assert(stack != NULL);
    void *stack_top = (char *)stack + STACK_SIZE;

    int child_pid = clone(child_func, stack_top, SIGCHLD, NULL);
    assert(child_pid != -1);

    int wstatus;
    if (waitpid(child_pid, &wstatus, 0) == child_pid) {
        printf("clone process successfully.\npid: %d\n", child_pid);
    } else {
        printf("clone process error.\n");
    }

    free(stack);
}

int main(void){
    test_clone();
    return 0;
}
