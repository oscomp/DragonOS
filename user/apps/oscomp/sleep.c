#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/time.h>
#include <assert.h>

int get_time() {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) {
        return -1;
    }
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

/*
 * 测试通过时的输出：
 * "sleep success."
 * 测试失败时的输出：
 * "sleep error."
 */
void test_sleep() {

	int time1 = get_time();
	assert(time1 >= 0);
	int ret = sleep(1);
	assert(ret == 0);
	int time2 = get_time();
	assert(time2 >= 0);

	if(time2 - time1 >= 1){	
		printf("sleep success.\n");
	}else{
		printf("sleep error.\n");
	}
}

int main(void) {
	test_sleep();
	return 0;
}
