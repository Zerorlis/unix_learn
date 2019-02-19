#include<iostream>
#include<unistd.h>
#include<fcntl.h>
using namespace std;
int main(int args,char* argv[])
{
    if (args!=2)
    {
        cout<<"usage:a.out file"<<endl;
        return 0;
    }
    if (access( argv[1],F_OK)<0)
    {
        cout <<"access error for "<<argv[1]<<endl;
    }
    else
    {
        cout<<"access ok for "<<argv[1]<<endl;
    }
    if (open(argv[1],O_RDONLY)<0)
    {
        cout <<"read error for "<<argv[1]<<endl;
    }
    else
    {
        cout<<"read ok for "<<argv[1]<<endl;
    }
    return 0;
}
