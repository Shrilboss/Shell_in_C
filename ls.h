#include "headers.h"

//command use to print the contents of a directory
int ls(int argc,char* argv[]){
    if(argc==1){
        struct dirent** current;
        int n=scandir(".",&current,NULL,alphasort); //scanning the pwd
        if(n==-1){
            //if no directory found
            printf("No file or directory named- \"%s\" found\n",argv[2]);
            return 1;
        }
        else{
            if (n!=2) //not prinitng the parent and current directory
            {
                while(n--){
                    //printing contents of the directory one by one
                    printf("%s  ",current[n]->d_name);
                    free(current[n]);
                    if(n==2) break; 
                }
                printf("\n");
                free(current); //freeing up memory
            }
        }
    }
    else{
        for(int i=1;i<argc;i++){
            const char* name;
            struct dirent** current;
            struct stat sb;
            int temp=0;
            name=argv[i]; //storing the name of the file/directory
            stat(argv[1],&sb);
            if(S_ISREG(sb.st_mode)){
                temp=1; //if the argument name is a file
            }
            //scanning the directory
            int n=scandir(name,&current,NULL,alphasort);
            if(n==-1){
                if(temp==1){
                    printf("%s\n",name);
                }
                else{
                    //if no directory found
                    printf("No file or directory named- \"%s\" found\n",argv[2]);
                    return 1;
                }
            }
            else{
                if (n!=2) //not prinitng the parent and current directory
                {
                    printf("%s:\n",argv[i]);
                    while(n--){
                        //printing contents of the directory one by one
                        printf("%s  ",current[n]->d_name);
                        free(current[n]);
                        if(n==2) break; 
                    }
                    printf("\n");
                    free(current); //freeing up memory
                }
            }
        }
    }
    return 1;
}