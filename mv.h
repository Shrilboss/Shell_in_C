#include "headers.h"

//function to move/rename files into another file/directory
int mv(int argc,char* argv[]){
    if(argc==1){
        printf("mv : missing file operand\n");
        return 1;
    }
    else if(argc==2){
        //no destionation source given
        printf("mv : missing destination file operand after \"%s\" \n",argv[1]);
        return 1;
    }
    else{
        struct stat sb;
        DIR* d=opendir(argv[argc-1]);
        char new[1000];
        if(d){ //if last argument is directory
            char newpath[1000];
            strcpy(newpath,argv[argc-1]);
            strcat(newpath,"/");
            for(int i=1;i<argc-1;i++){
                char filepath[1000];
                strcpy(filepath,newpath); //creating new path for the  destination file
                strcat(filepath,basename(argv[i]));  //basename extracts the file name
                int n=rename(argv[i],filepath); //moving files into directory
                if(n<0){
                    printf("Error while moving files please check destination path \n");
                    return 1;
                }
            }
            printf("Files moved successfully\n");
            return 1;
        }
        else{
            strcpy(new,argv[2]);
        }
        //rename moves/renames the source to dest file
        int n=rename(argv[1],new);
        if(n<0){
            printf("Error while moving files please check destination path \n");
            return 1;
        }
        else{
            printf("Files moved successfully\n");
            return 1;
        }
    }
}