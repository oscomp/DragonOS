#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
/*
 * 测试成功时输出：
 * "  Hello, mmap success"
 * 测试失败时输出：
 * "mmap error."
 */
void test_mmap(void) {
    char *array;
    const char *str = "  Hello, mmap success";
    int fd;
    struct stat st;

    fd = open("test_mmap.txt", O_RDWR | O_CREAT, 0666);
    assert(fd >= 0);

    write(fd, str, strlen(str));
    fstat(fd, &st);
    printf("file len: %ld\n", st.st_size);

    array = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (array == MAP_FAILED) {
        perror("mmap");
        printf("mmap error.\n");
    } else {
        printf("mmap content: %s\n", array);
        munmap(array, st.st_size);
    }

    close(fd);
}

int main(void){
    test_mmap();
    return 0;
}
