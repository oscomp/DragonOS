#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>

#define TEST_START(func) printf("Testing %s...\n", func)
#define TEST_END(func) printf("%s test completed.\n", func)

void test_write(){
    TEST_START(__func__);
    const char *str = "Hello operating system contest.\n";
    int str_len = strlen(str);
    
    // 使用 STDOUT_FILENO 而不是 STDOUT
    assert(write(STDOUT_FILENO, str, str_len) == str_len);
    TEST_END(__func__);
}

int main(void) {
    test_write();
    return 0;
}
