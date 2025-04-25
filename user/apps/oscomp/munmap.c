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
 static struct stat st;

 void test_munmap(void) {
     char *array;
     const char *str = "  Hello, mmap successfully!";
     int fd;
 
     fd = open("test_mmap.txt", O_RDWR | O_CREAT, 0666);  // 使用 O_CREAT 代替 O_CREATE
     assert(fd >= 0);
 
     write(fd, str, strlen(str));
     fstat(fd, &st);
     printf("file len: %ld\n", st.st_size);  // 使用 %ld 来打印 off_t 类型的 st_size
 
     array = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
     if (array == MAP_FAILED) {
         printf("mmap error.\n");
     } else {
         printf("mmap content: %s\n", array);
 
         // 尝试卸载映射区域
         int ret = munmap(array, st.st_size);
         printf("munmap return: %d\n", ret);
         assert(ret == 0);
 
         if (ret == 0)
             printf("munmap successfully!\n");
         else
             printf("munmap failed.\n");
     }
 
     close(fd);
 }

int main(void){
    test_munmap();
    return 0;
}
