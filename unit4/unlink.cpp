#include<iostream>
#include<fcntl.h>
#include <unistd.h>
using namespace std;

int main()
{
    if(open("test",O_RDWR)<0)
    {
        cout<<"open error";
        return 0;
    }
    if(unlink("test")<0)
    {
        cout<<"open error";
        return 0;
    }
    cout<<"unlink success";
    sleep(15);
    cout<<"done!";
    return 0;
}
