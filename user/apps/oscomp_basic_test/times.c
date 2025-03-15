#include "stdio.h"
#include <assert.h>
#include <unistd.h>
#include <sys/times.h>


struct tms mytimes;

void test_times()
{
    // TEST_START(__func__);

    // 获取进程的时间信息
    clock_t test_ret = times(&mytimes);
    assert(test_ret >= 0);

    // 输出时间信息，使用 %ld 来输出 long 类型
    printf("mytimes success\n{tms_utime:%ld, tms_stime:%ld, tms_cutime:%ld, tms_cstime:%ld}\n",
           mytimes.tms_utime, mytimes.tms_stime, mytimes.tms_cutime, mytimes.tms_cstime);

    // TEST_END(__func__);
}

int main(void)
{
    test_times();
    return 0;
}
