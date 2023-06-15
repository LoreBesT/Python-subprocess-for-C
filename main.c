#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    char *file = "mainbis.py"; //Enter the name of the python source file to be executed during a C process. Attention, the C file and the python one must be in the same folder

    char *newfile = realpath(file, NULL);
    if (newfile == NULL) {
        printf("Error getting file path!\n");
        return -1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        printf("Error creating child process!\n");
        return -1;
    } 
    
    else if (pid == 0) {
        // Child process code
        char *pythonFile = newfile;
        
        if (execlp("python3", "python3", pythonFile, NULL) == -1) {
            printf("Error executing Python file\n");
            return -1;
        }
    } 
    
    else {
        // Parent process code
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
        }
    }
    //from here on you can put all the rest of the code of the parent process, in C

    return 0;
}
