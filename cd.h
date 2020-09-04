#include "headers.h"

//function that changes the current working directory
int cd(int argc,char * argv[]){
    if(argc==1){
        printf("cd : directory name expected\n"); //error if no arguemnts given
    }
    else{
        struct stat sb;
        if(stat(argv[1],&sb)==-1){ //checking if the file/directory exists
            perror("cd");
        }
        else if(S_ISDIR(sb.st_mode)){ //checking if the path is of directory
            if(chdir(argv[1])!=0){ //chdir changes the directory
                printf("cd : No such directory\n");
            }
        }
        else{ //if its a file
            printf("cd : %s not a directory\n",argv[1]);
        }
    }
    return 1;
}