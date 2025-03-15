#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"  // 包含 gettimeofday() 函数
#include <assert.h>
/*
 * 测试通过时的输出：
 * "sleep success."
 * 测试失败时的输出：
 * "sleep error."
 */
void test_sleep() {
    // TEST_START(__func__);

    // 使用 gettimeofday 获取当前时间
    struct timeval start, end;
    gettimeofday(&start, NULL);  // 获取开始时间

    int ret = sleep(1);  // 睡眠1秒
    assert(ret == 0);

    gettimeofday(&end, NULL);  // 获取结束时间

    // 计算经过的时间差
    long time_diff = (end.tv_sec - start.tv_sec);
    if (time_diff >= 1) {  // 如果时间差大于等于1秒
        printf("sleep success.\n");
    } else {
        printf("sleep error.\n");
    }

    // TEST_END(__func__);
}

int main(void) {
    test_sleep();
    return 0;
}
