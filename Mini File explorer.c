#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>

char path[100]="/";

int display_subdirectories(char *p)
{
        printf("\n\nList of sub-directories under this directory\n\n");
        pid_t pid1=0;
        pid1=fork();
        if(pid1==0)
        {
                char *s[]={"ls",p,NULL};
                int c=execvp("ls",s);
                return c;
        }
        else
        {
                wait(NULL);
        }
}

int display_files(char *p)
{
        pid_t pid1=0;
        pid1=fork();
        if(pid1==0)
        {
                execlp("cat","cat",p,0);
                return 0;
        }
        else
        {
                wait(NULL);
        }
}

int check_file_type(char *p)
{
        pid_t pid1=0;
        pid1=fork();
        if(pid1==0)
        {
        char *s={"test","-d",p,NULL};
        int c=execvp("test",s);
        return c;
        }
        else
        {
                wait(NULL);
        }
}

void back()
{
        for(int i=strlen(path);i>=1;i--)
        {
                if(path[i]!='/')
                {
                        path[i]='\0';
                }
                else{
                        path[i]='\0';
                        return;
                }
        }
}

int main()
{
        pid_t pid=0;
        pid_t pid_1=0;
        int i=0;
        while(i>=0)
        {
                system("clear");
                printf("\t   <<<<<<<<<<FILE EXPLORER>>>>>>>>>>\n\n\n");
                printf("\t\t\t\tEnter 'back' to revert to the previous directory\n");
                printf("\t\t\t\tEnter 'exit' to quit the file explorer\n\n");
                printf("\nCurrent Path: %s",path);
                printf("\n\n");
                int b=display_files(path);
                char s[50];
                int c=display_subdirectories(path);
                printf("\nEnter the sub-directory you wish to move into:");
                scanf(" %s",s);
                if(strcmp(s,"back")==0)
                {
                        back();
                }
                else if(strcmp(s,"exit")==0)
                {
                        exit(0);
                }
                else{
                        if(i!=0)
                        {
                                strcat(path,"/");
                        }
                        strcat(path,s);
                }
                //int a = check_file_type(path);
                i++;
        }
}
