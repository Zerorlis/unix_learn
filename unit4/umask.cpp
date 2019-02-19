#include<fcntl.h>
#include<iostream>
#include<sys/stat.h>
using namespace std;
int main()
{
    umask(0);
    if(openat(AT_FDCWD,"test1",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH)<0)
        cout<<"create test1 error";
    umask(S_IRGRP|S_IROTH|S_IWGRP|S_IWOTH);

    if(open("test2",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH)<0)
        cout<<"create test2 error";
    
    if(creat("test3",S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH)<0)
        cout<<"create test3 error";
    return 0;
}
