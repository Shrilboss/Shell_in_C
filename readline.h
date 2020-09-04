#include "headers.h" 
//function to read lines from users
char *readline(void){
    int max=1024;
    int i=0;
    char *arr=malloc(sizeof(char)*1024); //allocating memory to arr
    int c;
    while(1){
        c=getchar();
        //while new line or EOF doesnt come, keep taking the input
        if(c==EOF || c=='\n'){
            arr[i]='\0';
            return arr;
        }
        else{
            arr[i]=c;
        }
        i++;
    }
}