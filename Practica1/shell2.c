#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <error.h>
#include <sys/wait.h>

#define MAX_ARGS 15
#define MAX_COMMANDS 15
#define MAX_ARG_LEN 20


void parser(char *buffer, char *args[MAX_COMMANDS][MAX_ARGS], char **redir, int *comandos){
    int i = 0, j = 0;
    if(!buffer) return;
    char *token = strtok(buffer, " \n");
    for(j = 0; token != NULL; j++){

        if(token && !strcmp(token, "|")){
            token = strtok(NULL, " \n");
            args[i][j+1] = NULL;
            j = 0;
            i++;
        }

        args[i][j] = token;

        if(j >= MAX_ARGS-1){
            printf("Numero maximo de argumentos alcanzado");
            exit(-1);
        }

        token = strtok(NULL, " \n");

    }

    *comandos = i+1;
    args[i+1][0] = NULL;
    // esto solo chequea el ultimo comando? 
    if(j >= 2 && args[i][j-2] && !strcmp(args[i][j-2], ">")){
       *redir = args[i][j-1];
        args[i][j-2] = NULL;
    }
    else
        args[i][j] = NULL;
    
    return;
}



int main()
{
    int ban = 1;
    char *logname = getenv("LOGNAME");
    char *buffer = malloc(sizeof(char)*100);

    while(ban){
        printf("%s > ", logname);
        fgets(buffer, 100, stdin);

        if(!strcmp(buffer, "exit\n")) exit(0);

        char *args[MAX_COMMANDS][MAX_ARGS];

        for(int i = 0; i<MAX_COMMANDS; i++) 
            for(int j = 0; j<MAX_ARGS; j++) 
                args[i][j] = NULL;

        char *redir = NULL;

        int comandos = 0;
        parser(buffer, args, &redir, &comandos);


        int fd[2];
        for(int i = 0; i < comandos; i++){
            int aux[2];
            aux[0] = fd[0]; aux[1] = fd[1];
            if(i != comandos-1) pipe(fd);
            if(fork() == 0){
                if(comandos != 1){
                    if(i != 0) {
                        dup2(aux[0], 0);
                        
                        close(aux[0]);
                        close(aux[1]);
                    }
                    if(i != comandos-1){
                        dup2(fd[1], 1);
                        close(fd[0]);
                        close(fd[1]);
                    }
                }

                if(redir && i == comandos-1) freopen(redir, "w+", stdout);
                execvp(args[i][0], args[i]);
            } else {
                if(i != 0) close(aux[0]);
                if(i != comandos-1)  close(fd[1]);
            }
        }
        pid_t wpid;
        while ((wpid = wait(&comandos)) > 0);
    }
    return 0;
}
