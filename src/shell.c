#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell_builtins.h"

#define READ_LINE_BUFFSIZE 1024
#define TOK_BUFFSIZE 64
#define TOK_DELIM "\t\r\n\a"

char *read_line(void){
    int buffsize = READ_LINE_BUFFSIZE;
    int positon = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[positon] = '\0';
            return buffer;
        }else{
            buffer[positon] = c;
        }
        ++positon;

        if(positon >= buffsize){
            buffsize += READ_LINE_BUFFSIZE;
            buffer = realloc(buffer, buffsize);
            if(!buffer){
                fprintf(stderr, "shell buffer allocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
    }

}

char **split_line(char *line){


    int buffsize = TOK_BUFFSIZE;
    int positon = 0;
    int tok_len;
    char **tokens = malloc(buffsize * sizeof(char*));
    char *token;
    char *token_cpy;

    if(!tokens){
        fprintf(stderr, "token buffer failed\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);

    while(token != NULL){
        tok_len = strlen(token);
        token_cpy = malloc((tok_len +1) * sizeof(char));
        strcpy(token_cpy, token);

        tokens[positon] = token_cpy;
        positon++;

        if(positon >= buffsize){
            tokens = realloc(tokens, buffsize);

            if(!tokens){
                fprintf(stderr, "token buffer reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[positon] = NULL;
    return tokens; 
}

int launch_shell(char **args){

    pid_t pid;
    pid_t wpid; 
    int status;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1){
            perror("shell fail");
        }
        exit(EXIT_FAILURE);
    }else if (pid < 0){
        perror("shell fail");
    }else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED); 
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;

}
int execute_shell(char **args){
    int x;

    if(args[0] == NULL){
        return 1;
    }
    for(x = 0; x < builtin_num(); ++x){
        if(strcmp(args[0], builtin_str[x]) == 0){
            return(*builtin_func[x])(args);
        }
    }
}
void free_args(char **args){
    char **iter = args; 
    while(*iter != NULL){
        free(*iter);
        ++iter;
    }
    free(args);
}
void run_shell_loop(){
    char *line; 
    char **args;
    int status;

    do{
        printf("CM_shell > ");
        line = read_line();
        args = split_line(line);
        status = execute_shell(args);
        free(line);
        free_args(args);
    }while(status);
}
int main(int argc, char *argv[])
{
    run_shell_loop();

    return EXIT_SUCCESS;
}
