#include <unistd.h>
#include <iostream>
#include "../myerror.h"
using namespace std;

int globVar = 6;
char buf[] = "a write to stdout\n";

int main(){
    int var;
    pid_t pid;

    var = 88;
    // 必须-1, 否则后面的输出会有问题，不能有结束的\0,后面就输出失败了
    if(write(STDOUT_FILENO, buf,sizeof(buf)-1)!=sizeof(buf)-1){
        err_sys("write error");
    }
    cout << "before fork\n";
    cout << "1\n";
    fflush(stdout);
    // 如果重定向，那么stdout是全缓冲
    if((pid = fork())<0){
        err_sys("fork error");
    } else if(pid == 0){
        // 父进程的内容
        cout << "f2\n";
        globVar ++;
        var ++;
    } else {
        cout << "s2\n";
        // 子进程的内容
        sleep(2);
    } 


    printf("pid = %ld, glob = %d , var = %d\n", (long)getpid(), globVar, var);
    exit(0);
}
