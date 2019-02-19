#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[])
{
    struct stat statbuf;
    int fd;
    struct timespec time[2];
    for(int i=1;i<argc;i++)
    {
        if(stat(argv[i],&statbuf)<0)
        {
            cout<<argv[i]<<" stat error"<<endl;
            continue;
        }
        if((fd=open(argv[i],O_RDWR|O_TRUNC))<0)
        {
            cout<<argv[i]<<" open error"<<endl;
            continue;
        }
        time[0]=statbuf.st_atim;
        time[1]=statbuf.st_mtim;
        if(futimens(fd,time)<0)
        {
            cout<<argv[i]<<" futimens error"<<endl;
            continue;
        }
        close(fd);
    }
    return 0;
}
