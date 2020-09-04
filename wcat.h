#include "headers.h"

//function that resembles the cat command of bash
int wcat(int argc,char* argv[]){
    FILE *fp;
    struct stat sb;
    if(argc==1){
        printf("No file specified \n"); //if no file is specified
        return 1;
    }
    else
    {
        for(int i=1;i<argc;i++){
            if(stat(argv[i],&sb)==-1){//if file does not exist
                printf("wcat : cannot open file\n");
                return 1;
            }
            if(S_ISDIR(sb.st_mode)){ //if entered path is a directory
                printf("wcat : %s is a directory\n",argv[i]);
                return 1;
            }
            else{
                fp=fopen(argv[i],"r"); //open file for reading
                char line[1000];
                if (fp==NULL)
                {
                    printf("wcat : cannot open file\n"); 
                    return 1;
                }
                else{
                    //recurse in the file and print each line
                    while(fscanf(fp,"%[^\n]\n",line)!=EOF){
                        printf("%s\n",line);
                    }
                fclose(fp); //close the file
                }
            }
        }
    }
    return 1;   
}
