#include "shell_builtins.h"

int (*builtin_func[])(char **) = {&shell_help, &shell_cd, &shell_create_dir,  &shell_exit};

char *builtin_str[] = {"help", "cd", "crdir", "exit"};

int builtin_num(){
    return sizeof(builtin_str) / sizeof(char*); 
}

int shell_help(char **args){
    int x;
    printf("welcome to chrinovic's shell\n");
    printf("type program names and arguments , and hit enter\n");
    printf("builtin in functions : \n");

    for(x = 0;x < builtin_num(); ++x){
        printf(" %s\n", builtin_str[x]);
    }
    return 1;
}

int shell_cd(char **args){

    if(!args || !args[1]){
        fprintf(stderr, "usage : cd <dir_name>\n");
        return 1;
    }
    if(chdir(args[1]) != 0){
        perror("cd");
        return 1;
    }
    return 0;
}

int shell_create_dir(char **args){
    if(!args || !args[1]){
        fprintf(stderr, "usage : crdir <dir_name>\n");
        return 1;
    }

    int dr = mkdir(args[1], 0755);
    if(dr == -1){
        perror("Error creating directory");
        return -1;
    }
    printf("%s directory created \n", args[1]);
    return 0;
}

int shell_exit(char **args){
    return 0;
}

