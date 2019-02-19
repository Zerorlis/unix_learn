#include "../myerror.h"
#include <unistd.h>

const static int BUFFSIZE = 4096;

int main()
{
    char buf[BUFFSIZE];
    int n; // 一次读取的个数
    while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
    {
        if(write(STDOUT_FILENO,buf,n)!=n)
        {
            err_sys("write error"); // 如果读取的内容也不是一样的说明有问题
        }
    }

    if(n<0) // read读取错误的时候会返回-1
    {
       err_sys("read error");
    }
    return 0;
}
