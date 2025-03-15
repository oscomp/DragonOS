#include <sched.h> // Include this header for sched_yield()
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define TEST_START(func) printf("Testing %s...\n", func)
#define TEST_END(func) printf("%s test completed.\n", func)

int test_yield() {
    // TEST_START(__func__);

    for (int i = 0; i < 3; ++i) {
        if (fork() == 0) {
            for (int j = 0; j < 5; ++j) {
                sched_yield(); // Yield CPU to other processes
                printf("  I am child process: %d. iteration %d.\n",
                       getpid(),
                       j);
            }
            exit(0);
        }
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < 3; ++i) {
        wait(NULL); // Wait for any child process to terminate
    }

    // TEST_END(__func__);
    return 0;
}

int main(void) {
    test_yield();
    return 0;
}
