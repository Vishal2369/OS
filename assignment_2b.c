#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    int child_pid;
    child_pid=fork();
    if(child_pid==0){
        child_pid=fork();
        if(child_pid==0){
            child_pid=fork();
        }
    }
    else{
        child_pid= 0;
        child_pid=fork();
        if(child_pid==0){
            child_pid=fork();
            if(child_pid>0){
                fork();
            }
        }
    }
}