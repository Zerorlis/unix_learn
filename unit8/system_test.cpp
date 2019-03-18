#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>


int system(const char * cmdString){
    int status;
    pid_t pid;
    if(cmdString == NULL){
        return(1);    
    }
    if((pid = fork())<0){
        status = -1;
    } else if(pid == 0){
        execl("/bin/sh","sh","-c",cmdString,(char *)0);
        _exit(127); // 如果excel出错，那么就返回-1，继续执行，所以直接退出
    } else{
        while(waitpid(pid, &status, 0)<0){
            // waitpid 出错的时候状态,感觉这里用if也可以，
            if(errno != EINTR){
                status = -1;
                break;
            }
        }
    }
    return(status); // 当fork失败，返回-1，当excel失败，返回127，当waitpid失败，返回-1，当waitpid失败，但是是被中断信号EINTR中断的，返回原来的status,信号中断也是个错误
}
int main(){
    system("./test.sh 1 2 4");
}
