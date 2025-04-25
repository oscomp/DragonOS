#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>

/*
 * 测试通过时应输出：
 * "  new fd is 3."
 */

void test_dup(){
	int fd = dup(STDOUT_FILENO); 
	assert(fd >=0);
	printf("  new fd is %d.\n", fd);
}

int main(void) {
	test_dup();
	return 0;
}
