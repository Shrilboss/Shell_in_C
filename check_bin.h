#include "headers.h"
//function that runs inbuilt binaries
int check_bin(int argc,char* argv[]){
    pid_t processid;
    int flag;
    processid = fork(); //creating a parallel process
    if(processid==0){
        if(execvp(argv[0],argv)==-1){ //execvp changes the flow of the program and transfers 
        //it to the terminal, based on the arguments and command name given, returns -1 in errors
            printf("No command found\n");
        }
        exit(EXIT_FAILURE);
    }
    else if(processid<0){
        printf("Couldn't fork\n"); //if there is forking error
    }
    else{
        waitpid(processid,&flag,WUNTRACED);//WUNTRACED waits until
        //child has not exited or stopped
    }
    return 1;
}