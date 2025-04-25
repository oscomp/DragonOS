#include "stdio.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "unistd.h"
#include <assert.h>

static char buffer[256];
void test_chdir(void){
    mkdir("test_chdir", 0777);
    int ret = chdir("test_chdir");
    printf("chdir ret: %d\n", ret);
    assert(ret == 0);
    char *cwd = getcwd(NULL, 0);  // 动态分配缓冲区
    if (cwd == NULL) {
        perror("getcwd failed");
        exit(EXIT_FAILURE);
    }
    printf("  current working dir : %s\n", cwd);
    free(cwd);  // 释放缓冲区
}

int main(void){
    test_chdir();
    return 0;
}
