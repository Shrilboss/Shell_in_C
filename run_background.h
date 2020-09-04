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
int run_background(int argc,char * argv[]){
    int status=1;
    pid_t process;
    process=fork();
    if(process==0){
        setpgid(0,0);
        if(argc==0){
            printf("No arguements given\n");
            return 1;
        }
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
        else if(strcmp(argv[0],"exit")==0) return 0;
        return check_bin(argc,argv);
    }
    else if (process<0)
    {
        perror("fork");
    }
    else{
        printf("Current process id: %d\n",process);
        waitpid(process,&status,WNOHANG);
    }
    return 1;
}