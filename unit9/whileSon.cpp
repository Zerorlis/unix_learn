#include <iostream>
#include "../myerror.h"
#include <unistd.h>
#include <stdlib.h>
void pr_ids(const char * name){
    std::cout << name << ":pid = " << getpid() << ";ppid = " << getppid() << ";pgrp= "<< getpgrp()<< std::endl;
}
int main(){
    pid_t pid;
    if((pid=fork())<0){
        err_sys("fork error");
    }else if(pid >0){
        pr_ids("parent");
       sleep(1); 
       std::cout << "finished" << std::endl;
    }else if(pid == 0){
        int i =0;
        sleep(5);
        while(i<10){
            pr_ids("son");
            std::cout << i << std::endl;
            i++;
        }
            exit(0);
    }
}
