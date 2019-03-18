/**
 * @file testfmemopen.cpp
 * @brief 测试fflush，fclose，fseek等对内存流的影响
 * @author Zerorlis
 * @version 0.1
 * @date 2019-02-20
 */

#include <cstdio>
#include "../apue.h"
const static int BSZ = 48;

int main() {
    FILE* fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'x';
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) err_sys("fmemopen error");
    printf("initial buffer content: %s \n", buf);
    fprintf(fp, "hello, world");
    printf("before fflush: %s \n", buf);
    fflush(fp);
    printf("after fflush: %s \n", buf);
    printf("len of string in buf = %1d \n", (long)strlen(buf));

    memset(buf, 'b', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'x';
    fprintf(fp, "hello, world");
    printf("before fseek: %s \n", buf);
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s \n", buf);
    printf("len of string in buf = %1d \n", (long)strlen(buf));

    memset(buf, 'c', BSZ - 2);
    buf[BSZ - 2] = '\0';
    buf[BSZ - 1] = 'x';
    fprintf(fp, "hello, world");
    printf("before fclose: %s \n", buf);
    fclose(fp);
    printf("after fclose: %s \n", buf);
    printf("len of string in buf = %1d \n", (long)strlen(buf));
}
