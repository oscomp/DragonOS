#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

/* 测试 unlink
 * 测试通过，应有如下输出：
 * "  unlink success!"
 * 测试失败，应有如下输出：
 * "  unlink error!"
 */

int test_unlink()
{
    int _ret = creat("./test_unlink", S_IRUSR | S_IWUSR);
	assert(_ret >= 0);
	write(_ret, "Hello, DragonOS!\n", 17);
	close(_ret);

    char *fname = "./test_unlink";
    int fd, ret;

    fd = open(fname, O_CREAT | O_WRONLY);
    assert(fd > 0);
    close(fd);

    // unlink test
    ret = unlink(fname);
    assert(ret == 0);
    fd = open(fname, O_RDONLY);
    if(fd < 0){
        printf("  unlink success!\n");
    }else{
	printf("  unlink error!\n");
        close(fd);
    }
    // It's Ok if you don't delete the inode and data blocks.

}

int main(void) {
	test_unlink();
	return 0;
}
