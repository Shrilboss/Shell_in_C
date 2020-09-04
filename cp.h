#include "headers.h"
//function used to copy file/directoryies into one another
int cp(int argc,char* argv[]){
    if(argc==1){
        printf("cp : missing file operand\n"); //few arguments
        return 1;
    }
    else if(argc==2){
        printf("cp : missing destination file operand after \"%s\" \n",argv[1]); //no destination file
        return 1;
    }
    //-r flag used to copy directories
    else if(strcmp(argv[1],"-r")==0){
        if (argc==3)
        {
            //no destination directory
            printf("cp : missing destination directory operand after \"%s\" \n",argv[2]);
            return 1;
        }
        else{
            struct stat sb1,sb2;
            char *dir1,*dir2;
            int k;
            dir1=argv[2];
            dir2=argv[3];
            if(stat(argv[2],&sb1)==-1){ //check if the first file/directory exists
                printf("%s : No such file or directory\n",argv[2]);
                return 1;                
            }
            if(stat(argv[3],&sb2)==-1){ //check if the second file/directory exists
                //make a new directory
                if((k=mkdir(argv[3],0777)) <0){
                    printf("mkdir : Cannot create new directory - %s\n",argv[3]);
                    return 1;
                }
            }
            stat(dir2,&sb2);
            //check if both the inputs are directories
            if(S_ISDIR(sb1.st_mode) && S_ISDIR(sb2.st_mode)){
                const char* name;
                name=argv[2];
                printf("%s \n",name);
                struct dirent** current;
                struct stat t;
                char path[1000];
                char oldpath[1000];
                int k;
                //creating an oldpath for dir1
                strcpy(oldpath,dir1);
                strcat(oldpath,"/");
                //creating a newpath for dir1
                strcpy(path,dir2);
                strcat(path,"/");
                strcat(path,dir1);
                //creating new directory inside the source
                if((k=mkdir(path,0777)) <0){
                    printf("mkdir : Cannot create new directory - %s\n",dir1);
                    return 1;
                }
                strcat(path,"/");
                //scanning the source dir
                int n=scandir(name,&current,NULL,alphasort); 
                while(n--){
                    char new[1000],newpath[1000];
                    strcpy(newpath,oldpath);
                    strcat(newpath,current[n]->d_name);
                    //creating newpath for the files of dir1
                    if(stat(newpath,&t)<0){
                        printf("error\n");
                        return 1;
                    }
                    if(S_ISREG(t.st_mode)){ //only if they are files
                        strcpy(new,path);
                        strcat(new,current[n]->d_name);  
                        FILE *src,*dest;
                        char c;
                        //opening the source file
                        src=fopen(newpath,"r");
                        if (src==NULL)
                        {
                            printf("Error reading %s file\n",current[n]->d_name);
                            return 1;
                        }
                        //opening a new file with the same name at destination
                        dest=fopen(new,"w");
                        if (dest==NULL)
                        {
                            printf("Error opening %s file\n",current[n]->d_name);
                            return 1;
                        }
                        //copying content fron source to destination
                        c=fgetc(src);
                        while(c!=EOF){
                            fputc(c,dest);
                            c =fgetc(src);
                        }
                        printf("Contents copied\n");
                        fclose(src);
                        fclose(dest);

                    }
                    free(current[n]);
                    if(n==2) break; //not taking the "." and ".." directories
                }               
                return 1;
            }
            else{
                // if directory name is invalid
                printf("Please enter a valid directory name\n");
                return 1;
            }
        }
    }
    //if -r flag is not there
    else{
        const char* t;
        struct stat sb;
        t=argv[argc-1];
        if(stat(t,&sb)==-1){ //check if the file/dorectory exists
            printf("%s : No such file or directory\n",t);
            return 1;
        }
        if(S_ISDIR(sb.st_mode)){ //checking if the destination is a directory
            for(int i=1;i<argc-1;i++){
                FILE *src,*dest;
                char destname[1000],c;
                src=fopen(argv[i],"r"); //opening the source file for reading
                if(src==NULL){
                    printf("Error reading \"%s\" file\n",argv[i]);
                    return 1;
                }
                //creating a new pathname for the destination file
                sprintf(destname,"%s/%s",argv[argc-1],basename(argv[i]));
                dest=fopen(destname,"w"); //opening the dest file for writing
                if(dest==NULL){
                    printf("Error writing to destination file \"%s\"\n",t);
                    return 1;
                }
                //copying content fron source to destination
                c=fgetc(src);
                while(c!=EOF){
                    fputc(c,dest);
                    c =fgetc(src);
                }
                printf("Contents copied\n");
                fclose(src);
                fclose(dest);                
            }
            return 1;
        }
        if(S_ISREG(sb.st_mode)) //checking if the destination is a file
        {
            for(int i=1;i<argc-1;i++){
                FILE *src,*dest;
                char c;
                src=fopen(argv[i],"r"); //opening source file for reading
                if(src==NULL){
                    printf("Error reading \"%s\" file\n",argv[i]);
                    return 1;
                }
                dest=fopen(t,"w"); //opening destination file for writing
                if(dest==NULL){
                    printf("Error writing to destination file \"%s\"\n",t);
                    return 1;
                }
                //copying content fron source to destination
                c=fgetc(src);
                while(c!=EOF){
                    fputc(c,dest);
                    c =fgetc(src);
                }
                printf("Contents copied\n");
                fclose(src);
                fclose(dest);
            }
            return 1;
        }

    }
    return 1;
}