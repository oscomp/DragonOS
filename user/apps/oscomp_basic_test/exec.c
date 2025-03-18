#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int is_executable(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0 && st.st_mode & S_IXUSR) {
        return 1;
    }
    return 0;
}

int main() {
    DIR *dir;
    struct dirent *entry;
    int program_executed = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_executable(entry->d_name)) {
            printf("正在执行: %s\n", entry->d_name);
            if (fork() == 0) {
                char path[256];
                snprintf(path, sizeof(path), "/bin/oscomp_basic_test/%s", entry->d_name);
                execl(path, entry->d_name, NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            }
            wait(NULL);
            program_executed = 1;
        }
    }

    closedir(dir);

    if (program_executed) {
        printf("所有程序已运行完毕，终止主程序。\n");
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}