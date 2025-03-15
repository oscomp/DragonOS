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

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_executable(entry->d_name)) {
            printf("正在执行: %s\n", entry->d_name);
            if (fork() == 0) {
                execl(entry->d_name, entry->d_name, (char *)NULL);
                perror("execl");
                exit(EXIT_FAILURE);
            }
            wait(NULL);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}