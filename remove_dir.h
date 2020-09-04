#include "headers.h"

//recursive function to remove directories
int remove_dir(char* dir){
    DIR *d = opendir(dir); //opening the current directory
    size_t len=strlen(dir);
    int flag=-1;
    if(d){ //if directory could be opened 
        struct dirent *g;
        flag=0;
        while(!flag && (g=readdir(d))){ //recurse in the directory
            int flag2=-1;
            char *val;
            size_t newpath;
            //check if the directory is not current(".") or parent ("..")
            if(!strcmp(g->d_name,".")|| !strcmp(g->d_name,".."))
                continue;
            else{
                newpath= len + strlen(g->d_name)+2;
                val = malloc(len);
                if(val){
                    struct stat sb;
                    //create a newpath to delete
                    snprintf(val,newpath,"%s/%s",dir,g->d_name);
                    if(!stat(val,&sb)){
                        if(S_ISDIR(sb.st_mode)){ //if its a directory
                            flag2=remove_dir(val); //recursively delete it
                        }
                        else{
                            flag2=remove(val); //else directly delete it
                            if(flag2<0){
                                printf("error\n");
                                return 0;
                            }
                        }
                    }
                    free(val);
                }
                flag=flag2; //update the flag variable
            }
        }
        closedir(d);
    }
    //if only file is remaining
    if(!flag){
        flag=remove(dir); //directly delete it
        if(flag<0){
            printf("error\n");
            return 0;
        }
    }
    return flag;
}