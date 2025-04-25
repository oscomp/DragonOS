#include "unistd.h"
#include "string.h"
#include <assert.h>

void test_write(){
	const char *str = "Hello operating system contest.\n";
	int str_len = strlen(str);
	assert(write(STDOUT_FILENO, str, str_len) == str_len);
}

int main(void) {
	test_write();
	return 0;
}
