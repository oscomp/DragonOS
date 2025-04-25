#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>
#include <assert.h>


void test_read() {
	int fd = open("./text.txt", 0);
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
