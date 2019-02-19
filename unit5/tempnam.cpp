/**
 * @file tempnam.cpp
 * @brief  测试tmpname和tmpfile
 * @author Zerorlis
 * @version 0.1
 * @date 2019-02-19
 */
#include <cstdio>
#include "../myerror.h"

int main(void) {
    char name[L_tmpnam], line[1024];
    FILE* fp;
    printf("%s\n", tmpnam(NULL));
    // 如果不提供空间，那么名字就是在某个静态区域，虽然指针还在，但是后面调用会重写这个名字
    tmpnam(name);
    printf("%s\n", name);
    if ((fp = tmpfile()) == NULL) err_sys("tempfile error");
    fputs("hello,this is a test", fp);
    rewind(fp);
    if (fgets(line, 1024, fp) == NULL) err_sys("readfile error");
    puts(line);
}
