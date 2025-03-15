#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/utsname.h>
#include <assert.h>
struct utsname un;

void test_uname() {
    int test_ret = uname(&un);
    assert(test_ret >= 0);

    printf("Uname: %s %s %s %s %s\n", 
        un.sysname, un.nodename, un.release, un.version, un.machine);
    
    // 如果需要域名信息，尝试打印 __domainname（如果存在）
    #ifdef __domainname
    printf("Domainname: %s\n", un.__domainname);
    #endif
}

int main(void) {
    test_uname();
    return 0;
}
