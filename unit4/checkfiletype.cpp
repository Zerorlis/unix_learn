#include <sys/stat.h>
#include <iostream>
#include "../myerror.h"

int main(int argc, char*argv[])
{
    if (argc < 2)
       std::cout<<"usage:a.out file1,file2,..."<<std::endl; 

    struct   stat filestatus;

   for (int i=1;i<argc;i++) 
   {
       std::cout << argv[i] << ":";
       if(lstat(argv[i],&filestatus)!=0)
       {
          err_ret("lstat error"); 
          continue;
       }
       mode_t mode = filestatus.st_mode;
       if S_ISREG(mode)
           std::cout<<"regular";
       else if S_ISDIR(mode)
           std::cout<<"directory";
       else if S_ISCHR(mode)
           std::cout<<"character special";
       else if S_ISBLK(mode)
           std::cout<<"block special";
       else if S_ISFIFO(mode)
           std::cout<<"fifo";
       else if S_ISLNK(mode)
           std::cout<<"sysmbolic link";
       else if S_ISSOCK(mode)
           std::cout<<"socket";
       else
           std::cout<<"unkown file";
       std::cout<<std::endl;
   }
   return 0;
}
