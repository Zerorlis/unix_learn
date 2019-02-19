# include <unistd.h> 
//unistd在unix头文件里面，不是iso c
# include <iostream>
# include "../myerror.h"
int main(void)
{
    if (lseek(STDIN_FILENO,0,SEEK_CUR)==-1)
    //这个时候，对fifo，标准输入，socket会返回-1
    {
        std::cout<<"cant seek.\n";
    }
    else
    {
        std::cout<<"seek ok.\n";
    }
    return 0;
}

