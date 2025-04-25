#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>
#include <assert.h>


void test_read() {
	int ret = creat("./text.txt", S_IRUSR | S_IWUSR);
	assert(ret >= 0);
	write(ret, "Hello, DragonOS!\n", 17);
	close(ret);	int fd = open("./text.txt", 0);
	char buf[256];
	int size = read(fd, buf, 256);
	assert(size >= 0);

	write(STDOUT_FILENO, buf, size);
	close(fd);
}

int main(void) {
	test_read();
	return 0;
}
