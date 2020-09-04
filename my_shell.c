//including header files
#include "headers.h"
#include "ls.h"
#include "cd.h"
#include "check_bin.h"
#include "chmod.h"
#include "cp.h"
#include "mkdir.h"
#include "mv.h"
#include "pwd.h"
#include "readline.h"
#include "remove_dir.h"
#include "rm.h"
#include "split.h"
#include "wcat.h"
#include "wgrep.h"

//program to run a process in background
int run_background(int argc,char * argv[]){
    int status=1;
    pid_t process;
    process=fork(); //forking to create a parallel process
    if(process==0){
        setpgid(0,0); /*sets  the  PGID of the process specified by pid to pgid.  If
       pid is zero, then the process ID of the calling process  is  used.   If
       pgid is zero, then the PGID of the process specified by pid is made the
       same as its process ID.*/
        if(argc==0){
            printf("No arguements given\n");
            return 1;
        }
        else if(strcmp(argv[0],"ls")==0){ return ls(argc,argv);}  //calling ls
        else if(strcmp(argv[0],"wgrep")==0){ return wgrep(argc,argv); } //calling wgrep
        else if(strcmp(argv[0],"wcat")==0){return wcat(argc,argv); } //calling wcat
        else if(strcmp(argv[0],"mv")==0){ return mv(argc,argv); } //calling mv
        else if(strcmp(argv[0],"cp")==0){ return cp(argc,argv); } //calling cp
        else if(strcmp(argv[0],"cd")==0){ return cd(argc,argv); } //calling cd
        else if(strcmp(argv[0],"pwd")==0){ return pwd(argc,argv); } //calling pwd
        else if(strcmp(argv[0],"rm")==0){ return rm(argc,argv); } //calling rm
        else if(strcmp(argv[0],"chmod")==0){ return ch_mod(argc,argv); } //calling chmod
        else if(strcmp(argv[0],"mkdir")==0){ return mk_dir(argc,argv);} //calling mk_dir
        else if(strcmp(argv[0],"exit")==0) return 0; //exiting the function
        return check_bin(argc,argv); //checking for binary commands
    }
    else if (process<0)
    {
        perror("fork"); //error if forking failed
    }
    else{
        printf("Current process id: %d\n",process); //printing current process id
        waitpid(process,&status,WNOHANG); //WNOHANG returns immediately if no child exited
    }
    return 1;
}
int start_shell(int argc,char* argv[]){
    if(argc==0){
        printf("No arguements given\n"); //error if there are 0 arguements
        return 1;
    }
    else if (strcmp(argv[argc-1],"&")==0) //checking for "&" at the end
    {
        argc-=1;  //decreasing count by 1
        argv[argc]=NULL; //making last argument NULL
        return run_background(argc,argv); //running the command in background
    }
    //checking for inbuilt commands
    else if(strcmp(argv[0],"ls")==0){ return ls(argc,argv);}
    else if(strcmp(argv[0],"wgrep")==0){ return wgrep(argc,argv); }
    else if(strcmp(argv[0],"wcat")==0){return wcat(argc,argv); }
    else if(strcmp(argv[0],"mv")==0){ return mv(argc,argv); }
    else if(strcmp(argv[0],"cp")==0){ return cp(argc,argv); }
    else if(strcmp(argv[0],"cd")==0){ return cd(argc,argv); }
    else if(strcmp(argv[0],"pwd")==0){ return pwd(argc,argv); }
    else if(strcmp(argv[0],"rm")==0){ return rm(argc,argv); }
    else if(strcmp(argv[0],"chmod")==0){ return ch_mod(argc,argv); }
    else if(strcmp(argv[0],"mkdir")==0){ return mk_dir(argc,argv);}
    //exiting the function
    else if(strcmp(argv[0],"exit")==0) return 0;
    return check_bin(argc,argv); //checking for binary commands
}

//main function
int main(int argc,char* argv[]){

    char *input;
    char **args;
    int status=1,count;
    printf("--------------WELCOME TO MY SHELL--------------\n");
    while(status){ //running a loop while status is true
        count=0;
        char path[1000];
        if(getcwd(path,sizeof(path))!=NULL){
            printf("%s",path); //printing the present directory path
        }
        printf(">> ");
        input=readline(); //reading input from user
        args = split(input); //parsing the input 
        int j=0;
        while(args[j]!=NULL){
            count+=1; //counting no. of arguments
            j++;
        }
        status=start_shell(count,args); //starting the shell
        //freeing memory
        free(input);
        free(args);
    }
    return EXIT_SUCCESS; //end of shell
}
