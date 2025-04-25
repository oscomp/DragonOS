#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h> 

#include <assert.h>

struct utsname un;

void test_uname() {
	int test_ret = uname(&un);
	assert(test_ret >= 0);

	printf("Uname: %s %s %s %s %s %s\n", 
		un.sysname, un.nodename, un.release, un.version, un.machine, un.__domainname);

}

int main(void) {
	test_uname();
	return 0;
}
