#include "executor.h"
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



static int extractRedirections(char **args, char **inFile, char **outFile) {
    if (args == NULL || args[0] == NULL) {
        return 0;
    }

    *inFile = NULL;
    *outFile = NULL;

    int j = 0;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            if (args[i + 1] == NULL || strcmp(args[i + 1], ">") == 0 || strcmp(args[i + 1], "<") == 0) {
                fprintf(stderr, "mish: error de sintaxis cerca de '>'\n");
                return -1;
            }
            *outFile = args[i + 1];
            i++;
        } else if (strcmp(args[i], "<") == 0) {
            if (args[i + 1] == NULL || strcmp(args[i + 1], ">") == 0 || strcmp(args[i + 1], "<") == 0) {
                fprintf(stderr, "mish: error de sintaxis cerca de '<'\n");
                return -1;
            }
            *inFile = args[i + 1];
            i++;
        } else {
            args[j++] = args[i];
        }
    }

    args[j] = NULL;

    if (*inFile != NULL || *outFile != NULL) {
        return 1;
    }
    return 0;
}

int executeCommand(char **args){
 if(args == NULL || args[0] == NULL)
	 return 0;

 char *inFile, *outFile;
 int redirectionResult = extractRedirections(args, &inFile, &outFile);
 
 if (redirectionResult == -1 || args[0] == NULL)
    return -1;
 
 pid_t pid = fork();


 if( pid < 0 ){
	 perror("fork");
	 return -1;
 }
 else if( pid == 0){
    int fd;
    if( inFile != NULL ){
        fd = open(inFile, O_RDONLY);
        if(fd == -1){
            perror("mishell error in file");
            _exit(EXIT_FAILURE);
        }
        if(dup2(fd, STDIN_FILENO) == -1){
            perror("mishell error in dup2");
            _exit(EXIT_FAILURE);
        }
        close(fd);
    }
    if( outFile != NULL){
        fd = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
        if( fd == -1){
            perror("mishell error out file");
            _exit(EXIT_FAILURE);
        }
        if(dup2(fd, STDOUT_FILENO) == -1){
            perror("mishell error in dup2");
            _exit(EXIT_FAILURE);
        }
        close(fd);
    }
    if(execvp(args[0], args) == -1){
        perror("mishell error");
    }
    _exit(EXIT_FAILURE);
    
 }

 else{
	int status;	
	if(waitpid(pid, &status, 0) == -1){
		perror("waitpid");
		return -1;
	}
	return 0;
 }
}
