#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/times.h>  



struct tms mytimes;

void test_times() {
    clock_t test_ret = times(&mytimes);
    assert(test_ret >= 0);

    printf("mytimes success\n{tms_utime: %ld, tms_stime: %ld, tms_cutime: %ld, tms_cstime: %ld}\n",
           mytimes.tms_utime, mytimes.tms_stime, mytimes.tms_cutime, mytimes.tms_cstime);
}

int main(void)
{
	test_times();
	return 0;
}
