#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

/*
 * 能通过测试则输出：
 * "  getppid success. ppid : [num]"
 * 不能通过测试则输出：
 * "  getppid error."
 */

int test_getppid()
{
    pid_t ppid = getppid();
    if(ppid > 0) printf("  getppid success. ppid : %d\n", ppid);
    else printf("  getppid error.\n");
    return 0;
}

int main(void) {
	test_getppid();
	return 0;
}
