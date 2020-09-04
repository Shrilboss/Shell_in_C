#include "headers.h"
//used to change permissions of a given file
int ch_mod(int argc,char * argv[]){
    if(argc==1){
        printf("chmod : missing operands\n"); //if fewer arguemnts are given
        return 1;
    }
    else if(argc==2){
        printf("chmod : missing operands after %s \n",argv[1]); //if no mode is given
        return 1;
    }
    else{
        int k,i;
        i=strtol(argv[1],0,8); //converts argument into octal
        if(k=chmod(argv[2],i)<0) printf("chmod : Cannot change permissions of the given file or directory\n");
        //chmod takes in the file name and mode and changes it permission according to the mode given
        return 1;
    }
}