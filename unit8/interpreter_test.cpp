#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "../myerror.h"

int main(){
    pid_t pid;
    if((pid=fork())<0){
        err_sys("fork error");
    } else if(pid==0){
        if(execlp("./test.sh","echo 1","echo 2","echo 3","echo 4","echo 5",(char *)0)<0){
            err_sys("execl error");    
        }
    }
    if(waitpid(pid, NULL, 0) <0)
        err_sys("waitpid error");
    exit(0);

}
