#include "headers.h"

//function to parse the input and split acc to spaces
char **split(char* string){
    int max=1024,i=0;
    char **ans=malloc(max*sizeof(char *)); //create a new array of strings
    char *val = strtok(string," "); //strtok splits acc to given delimiter
    while (val!=NULL)
    {
        ans[i]=val;
        i++;
        val=strtok(NULL," ");
    }
    ans[i]=NULL; //make last element NULL
    return ans;

}