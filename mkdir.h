#include "headers.h"

//function to create a new empty directory
int mk_dir(int argc,char * argv[]){
    if(argc==1){
        printf("mkdir : missing operands\n");
        return 1;
    }
    else{
        for(int i=1;i<argc;i++){
            int k;
            //mkdir make a new directory witht the  given mode as permission (0777)
            if((k=mkdir(argv[i],0777)) <0){
                printf("mkdir : Cannot create new directory - %s\n",argv[i]);
                return 1;
            }
        }
        return 1;
    }
}