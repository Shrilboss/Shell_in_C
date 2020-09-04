#include "headers.h"

//function to remove a file or directory
int rm(int argc,char * argv[]){
    if(argc==1){
        printf("rm : missing operand\n");
        //if no argument are given
        return 1;
    }
    //if -r flag exists then delete directory
    else if(strcmp(argv[1],"-r")==0){
        int k;
        if(argc==2){
            printf("rm : missing operand\n"); //need atleast one dir path
            return 1;
        }
        else{
            //call remove dir for each directory
            for(int i=2;i<argc;i++){
                if((k=remove_dir(argv[i]))) printf("rm : Cannot remove %s : No such file or directory\n",argv[2]);
            }
            return 1;
        }
    }
    else{
        //Deleting files
        int k;
        for(int i=1;i<argc;i++){
            //remove function directly deletes a file 
            if((k=remove(argv[i]))<0) printf("rm : Cannot remove %s : No such file or directory\n",argv[2]);
        }
        return 1;
    }
}