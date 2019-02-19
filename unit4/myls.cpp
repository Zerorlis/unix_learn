#include <dirent.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    DIR * dp;
    struct dirent * dirp; 
    if (argc < 2)
    {
        cout<<"usage a.out file1 file2 ...";
        return 0;
    }

    for(int i=1;i<argc;i++)
    {
        if ((dp=opendir(argv[i]))==NULL)
        {
            cout<<"can't open dir "<<argv[i]<<endl;
            continue;
        }
        cout<<argv[i]<<":";
        while ((dirp=readdir(dp))!=NULL)
        {
            cout<<dirp->d_name<<" ";
        }
        cout<<endl;
    }
    return 0;
}
