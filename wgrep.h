#include "headers.h"

//function that resembles the grep command of bash
int wgrep(int argc,char* argv[]){
    FILE *fp;
    if(argc==1){
        printf("wgrep: searchterm [filename ...]\n"); //if no argument specified
        return 1;
    }
    else if (argc==2)
    {
        //if only pattern is specified
        char line[1000];
        while (1)
        {
            char line[1000];
            fgets(line,1000,stdin); //then check in stdin 
            if(strstr(line,argv[1])!=NULL){ //check if the pattern exists in the input
                printf("%s\n",line); //print it
            }
            else{
                continue;
            }
        }
    }
    else
    {
        char * patt=argv[1]; //store the pattern
        struct stat sb;
        for(int i=2;i<argc;i++){
            if (stat(argv[i],&sb)==-1) //check if file exists
            {
                fprintf(stderr,"wgrep: cannot open file named- \"%s\" \n",argv[i]);
                return 1;
            }
            if(S_ISDIR(sb.st_mode)){ //if the entered path is a directory
                printf("ERROR !! - Please enter file not directory\n");
                return 1;
            }
            else
            {
                fp = fopen(argv[i],"r"); //open file for reading
                char line[1000];
                if (fp==NULL)
                {
                    printf("wgrep: cannot open file named- \"%s\" \n",argv[i]);
                    return 1;
                }
                else{
                    int t=strlen(patt),k=0,flag=0;
                    char temp[1000];
                    int a=patt[0];
                    int b=patt[t-1];
                    if(a==34 && b==34 || a==39 && b==39){ //check if pattern is in form of "  "
                        flag=1;
                        for(int i=1;i<t-1;i++){
                            temp[k]=patt[i];
                            k++;
                        }
                        temp[k]='\0'; //remove the "" and store it in temp 
                    }
                    if (flag)
                    {
                        while(fscanf(fp,"%[^\n]\n",line)!=EOF){ //iterate in the file
                            if(strstr(line,temp)!=NULL){ //check if the pattern exists as a substring
                                printf("%s\n",line); //print that line
                            }
                            else{
                                continue;
                            }
                        }
                    }
                    else{
                        while(fscanf(fp,"%[^\n]\n",line)!=EOF){ //iterate in the file
                            if(strstr(line,patt)!=NULL){ //check if the pattern exists as a substring
                                printf("%s\n",line); //print that line
                            }
                            else{
                                continue;
                            }
                        }
                    }
                fclose(fp); //close the file
                }
            }
        }
    }
}  