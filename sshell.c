#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


#define CMDLINE_MAX 512

int main(void)
{
        char cmd[CMDLINE_MAX];
     /*   char content[MAX_WORDS];
        char file[MAX_WORDS];
        FILE* fp;*/

        while (1) {
                char *nl;
                //int retval;

                /* Print prompt */
                printf("sshell$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';

                /* Builtin command */
                if (!strcmp(cmd, "exit")) {
                        fprintf(stderr, "Bye...\n");
                        break;
                }
              
               

                /* Regular command */
                pid_t pid;
                //char command = NULL;
                //char* args[16] = {"echo","hello",NULL};
                
                char* args[16];   
                char* temcmd=malloc(32);
                char* temcmd2 = malloc(32);
                strcpy(temcmd, cmd);
                strcpy(temcmd2, cmd);
                /*
        //phase4
        char content[MAX_WORDS];
        char file[MAX_WORDS];
        FILE *fp;
        char * redirect;
        int count = 0;
        const char * operator = (char *)'>';

        //test if there exists redirection
        redirect = strstr (cmd,">");

        if(redirect != NULL)//if there exists >
        {
            for(int n = 0; n<count; n++)
            {
                if(strcmp(operator,args[n])==0)//find where is >
                {
                    strcpy(file,args[n+1]);//file name is after >
                        for(int a = 1; a<n-1; a++)//file content is before >
                        {
                            strcpy (content, args[a]);//copy all the words in char content
                        }                           
                }
            }
        }
        //write and open file
        fp = fopen(file, "w+");
        fputs(content, fp);
        fclose(fp);
*/
                //const char* operator = (char*)'>';

                //if (redirect != NULL)//if there exists >
                //{
                //    for (int n = 0; n < count; n++)
                //    {
                //        if (strcmp(operator,args[n]) == 0)//find where is >
                //        {
                //            strcpy(file, args[n + 1]);//file name is after >

                //            //fgets(content, MAX_WORDS, stdin);

                //            for (int a = 1; a < n - 1; a++)//file content is before >
                //            {
                //                strcpy(content, args[a]);//copy all the words in char content
                //            }

                //        }
                //    }

                //}
                ////write and open file 
                //fp = fopen(file, "w+");
                //fputs(content, fp);
                //fclose(fp);
                char* stringsplit=strtok(temcmd, " ");
                //Output redirection
                if (strstr(temcmd2, ">") != NULL) {
                    //Determine whether our command contains the ">" symbol
                    char* temstr = strtok(temcmd2, ">");
                    

                    for (int n = 0; n < 16; n++) {
                        if (temstr != NULL) {
                            args[n] = temstr;
                            temstr = strtok(NULL, " ");
                           
                        }
                        else {
                            args[n] = NULL;

                        }
                    }
                    int fd;
                    //Output file
                    fd = open(args[3], O_WRONLY | O_CREAT, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    return 0;
                    
                }
                else {
                    //if there is no ">" in our command, then put the command in the args
                    for (int n = 0; n < 16; n++) {
                        if (stringsplit != NULL) {
                            args[n] = stringsplit;
                            stringsplit = strtok(NULL, " ");
                        }
                        else {
                            args[n] = NULL;

                        }
                    }
                }
                //execute CD operation
                if (!strcmp(args[0], "cd")) {
                    char cwd[CMDLINE_MAX];

                    getcwd(cwd, sizeof(cwd));

                    chdir(args[1]);

                }

             
                pid = fork();
                if (pid == 0) {
                    /* Child */
                    
                    execvp(args[0],args);
                    perror("execv");
                    exit(1);
                    
                }
                else if (pid > 0) {
                    /* Parent */
                    int status;
                    waitpid(pid, &status, 0);
                   
                    
                    fprintf(stderr, "+ completed '%s' [%d]\n", cmd, WEXITSTATUS(status));
                    
                }
                else {
                    perror("fork");
                    
                }
                //execute pwd operation
                if (!strcmp(cmd, "pwd")) {
                    char cwd[CMDLINE_MAX];
                    getcwd(cwd, sizeof(cwd));

                }
              
              
        }

        return EXIT_SUCCESS;
}
