#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#define CMDLINE_MAX 512
#define MAX_WORDS 512
int main(void)
{
        char cmd[CMDLINE_MAX];
        char content[MAX_WORDS];
        char file[MAX_WORDS];
        FILE *fp;

   
        while (1) {
                char *nl;
                //int retval;
                //retval = 0;
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
                if (!strcmp(cmd, "pwd")) {
                    fprintf(stderr, "pwd...\n");
                    
                }

                /* Regular command */
                pid_t pid;
                //char command = NULL;
                //char* args[16] = {"echo","hello",NULL};
                
                char* args[16];
                char* temcmd=malloc(32);
                strcpy(temcmd, cmd);
                char* stringsplit=strtok(temcmd, " ");
               
                char * redirect;
                
               

                //test if there exists redirection
                redirect = strstr (cmd,">");
                

                int count = 0;

                for (int n = 0; n < 16; n++) {
                    if (stringsplit != NULL) {
                        args[n] = stringsplit;
                        stringsplit = strtok(NULL, " ");
                        count++;//count of total words
                    }
                    else {
                        args[n] = NULL;

                    }
                }
                //phase4
                const char * operator = (char *)'>';
                
                if(redirect != NULL)//if there exists >
                {
                    for(int n = 0; n<count; n++)
                    {
                        if(strcmp(operator,args[n])==0)//find where is >
                        {
                            strcpy(file,args[n+1]);//file name is after >
                            
                            fgets(content, MAX_WORDS, stdin);
                            /*
                            for(int a = 1; a<n-1; a++)//file content is before >
                            {
                                strcpy (content, args[a]);//copy all the words in char content
                            }
                            */
                        }
                    }

                }
                //write and open file
                fp = fopen(file, "w+");
                fputs(content, fp);
                fclose(fp);
                if (!strcmp(args[0], "cd")) {
                    char cwd[CMDLINE_MAX];

                    getcwd(cwd, sizeof(cwd));

                    chdir(args[1]);

                }
                pid = fork();
                if (pid == 0) {
                    /* Child */
                    //execvp(cmd, args[0]);
                    execvp(args[0],args);
                    perror("execv");
                    exit(1);
                    
                }
                else if (pid > 0) {
                    /* Parent */
                    int status;
                    waitpid(pid, &status, 0);
                    //printf("Child returned %d\n",
                       // WEXITSTATUS(status));
                    fprintf(stderr, "+ completed '%s' [%d]\n", cmd, WEXITSTATUS(status));
                }
                else {
                    perror("fork");
                    
                }
                if (!strcmp(cmd, "pwd")) {
                    char cwd[CMDLINE_MAX];
                    getcwd(cwd, sizeof(cwd));

                }
                
                
                //return retval;
                //retval = system(cmd);
               /* fprintf(stdout, "Return status value for '%s': %d\n",
                        cmd, retval);*/
        }

        return EXIT_SUCCESS;
}
