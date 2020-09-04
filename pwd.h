#include "headers.h"
//code to print the present working directory
int pwd(int argc,char * argv[]){
    char path[1000];
    //getcwd stores the value of pwd in path
    if(getcwd(path,sizeof(path))!=NULL){
        printf("%s\n",path);
    }
    else{
        printf("Couldn't print the path\n");
        return 1;
    }
    return 1;
}