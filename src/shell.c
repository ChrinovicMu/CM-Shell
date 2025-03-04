#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include "shell_builtins.h"

#define READ_LINE_BUFFSIZE 1024
#define TOK_BUFFSIZE 64
#define TOK_DELIM " \t\r\n\a"

char *read_line(void){
    int buffsize = READ_LINE_BUFFSIZE;
    int positon = 0;
    char *buffer = malloc(sizeof(char) * buffsize);

    if(!buffer){
        fprintf(stderr, "buffer allocation failed\n");
        exit(EXIT_FAILURE);
    }
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

    while(isspace((unsigned char)*line)){
        line++;
    }
    char *end = line +strlen(line) - 1;
    while(end > line && isspace((unsigned char)*end)){
        end--;
    }
    end[1] = '\0';

    token = strtok(line, TOK_DELIM);

    while(token != NULL){
        
        token_cpy = strdup(token);
        if(!token_cpy){
            fprintf(stderr, "token token_cpy allocation failed\n");
            exit(EXIT_FAILURE);
        }

        tokens[positon] = token_cpy;
        printf("toekn %d : %s\n", positon, token_cpy);
        positon++;

        if(positon >= buffsize){

            buffsize += TOK_BUFFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char*));

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
            if(wpid == -1){
                perror("waitpid");
                return 1;
            }
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
            printf("CALLING BUILTIN FUNCTION %s\n", builtin_str[x]);
            return(*builtin_func[x])(args);
        }
    }
    return launch_shell(args);
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
