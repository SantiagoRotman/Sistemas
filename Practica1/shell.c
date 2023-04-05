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
#define MAX_ARG_LEN 20


void parser(char *buffer, char *args[MAX_ARGS], char **redir){
    int i;
    char *token = strtok(buffer, " \n");
    
    for(i = 0; token != NULL; i++){
        args[i] = token;

        if(i >= MAX_ARGS-1){
            printf("Numero maximo de argumentos alcanzado");
            exit(-1);
        }

        token = strtok(NULL, " \n");
    }

    if(!strcmp(args[i-2], ">")){
       *redir = args[i-1];
        args[i-2] = NULL;
    }
    else
        args[i] = NULL;
    
    return;
}

int main()
{
    int ban = 1;
    char *logname = getenv("LOGNAME");
    // tiene tamaño 100 para que entre todo el comando
    char *buffer = malloc(sizeof(char)*100);

    while(ban){
        printf("%s > ", logname);
        fgets(buffer, 100, stdin);

        char *args[MAX_ARGS];
        char *redir = NULL;

        parser(buffer, args, &redir);

        if(fork() == 0){
            if(redir) freopen(redir, "w+", stdout);
            execvp(args[0], args);
        }
        else
            wait(0);
    }
    return 0;
}