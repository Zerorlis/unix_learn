/**
 * @file testmkstemp.cpp
 * @brief 测试mkstemp 和 mkdtemp,位于stdlib.h
 * @author Zerorlis
 * @version 0.1
 * @date 2019-02-19
 */

#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include "../myerror.h"

void make_temp(char* templatename);

int main() {
    char good_templatename[] = "/tmp/dirXXXXXXX";  // 必须要6个X
    char* bad_templatename =
        "/tmp/dirXXXXXXX";  // 不建议，因为这个指针指向的对象不可修改，会出现段错误
    printf("try to create tempfile ...\n");

    make_temp(good_templatename);

    printf("try to create tempfile ...\n");

    make_temp(bad_templatename);
}

void make_temp(char* templatename) {
    int fd;
    struct stat sbuf;  // 这个是文件的属性的结构体，具体见书75页

    if ((fd = mkstemp(templatename)) < 0) {
        err_sys("cant create tempfile");
    }
    printf("create temp file : %s\n", templatename);

    if (stat(templatename, &sbuf) < 0) {
        if (errno == ENOENT)
            printf("file doesn't exist");
        else
            err_sys("stat failed");
    } else {
        printf("file exists\n");
        unlink(templatename);
    }
}
