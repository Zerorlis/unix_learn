#include<fcntl.h>
#include<iostream>
#include"../myerror.h"
#include<unistd.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";
int main(void)
{
    int fd; //文件描述符
    if ((fd=creat("file.hole",S_IRUSR|S_IWUSR|S_IRGRP|S_IXOTH))<0)
    {
        err_sys("creat error");
    }
    if (write(fd,buf1,10)!=10)
    {
        err_sys("buf1 write error");
    }
    //作用移动当前的文件描述符，如果是0可以达到获取当前描述符的效果，注意，不能使用管道
    if (lseek(fd, 16384,SEEK_SET)==-1)
    {
        err_sys("lseek error");
    }
    if (write(fd,buf2,10)!=10)
    {
        err_sys("buf2 write error");
    }
    return 0;

}
