#include "../myerror.h"
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
void pr_exit(int);
int main(){
    pid_t pid;
    int status;

    if((pid = fork())<0){
        err_sys("fork error");
    } else if(pid == 0){
        exit(7);
    }

    if(wait(&status)!=pid){
        err_sys("wait error");
    }

    pr_exit(status);

    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        abort();
    }

    if(wait(&status)!=pid){
        err_sys("wait error");
    }

    pr_exit(status);

    
    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        status = 1/0;
    }

    if(wait(&status)!=pid){
        err_sys("wait error");
    }

    pr_exit(status);

    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid == 0){
        kill(getpid(),SIGTSTP);
    }

    if(waitpid(pid, &status, WUNTRACED)!=pid){
        err_sys("wait error");
    }

    pr_exit(status);
    
    sleep(10);

    exit(0);
}


void pr_exit(int status){
    if(WIFEXITED(status)){
        cout << "normal termination, exit status = " << WEXITSTATUS(status) << endl;
    } else if(WIFSIGNALED(status)){
        cout << "abnormal termination, signal number = " << WTERMSIG(status)
#ifdef WCOREDUMP
            << (WCOREDUMP(status) ? ",core file generated" : "") << endl;}
#else
            << endl;}
#endif
    else if(WIFSTOPPED(status)){
        cout << "child stopped, signal number = " << WSTOPSIG(status) << endl;
    }
}

