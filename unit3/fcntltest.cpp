# include <iostream>
# include "../myerror.h"
# include <unistd.h>
# include <iostream>
# include <fcntl.h>
int main(int args, char* argv[])
{
    int fileflag=2;
    if (args!=2)
    {
        std::cout<<"usage:a.out <descroptor>";
    }
    // 这里的atoi是用于转化字符为数字
    if((fileflag=fcntl(atoi(argv[1]),F_GETFL,0))<0)
    {
        err_sys("fcntl error for fd %d",atoi(argv[1]));
    }
    switch(fileflag&O_ACCMODE)
    {
        case O_RDONLY:
            std::cout<<"read only";
            break;
        case O_WRONLY:
            std::cout<<"write only";
            break;
        case O_RDWR:
            std::cout<<"read write";
            break;
        default:
            std::cout<<"unknow access mode;";
    }
    if (fileflag&O_APPEND)
    {
        std::cout<<",append";
    }
    if(fileflag&O_NONBLOCK)
    {
        std::cout<<",NoBloking";
    }
    if(fileflag&O_SYNC)
    {
        std::cout<<",Synchronous writes";
    }
#if !defined(_POSIX_C_SOURCE)&& defined(O_FSYNC)&& (O_FSYNC!=O_SYNC)
    if (fileflag&O_FSYNC)
    {
        std::cout<<"synchronous write";
    }
#endif
    std::cout<<std::endl;
    return 0;
}
    
