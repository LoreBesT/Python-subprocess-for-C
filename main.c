#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    char *file = "mainbis.py"; //Inserisci il nome del file sorgente in python da eseguire durante un processo in C. Attenzione il file in C e quello in python dovranno trovarsi nella stessa cartella

    char *newfile = realpath(file, NULL);
    if (newfile == NULL) {
        printf("Errore nel ricavare il percorso del file!\n");
        return -1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        printf("Errore nella creazione del processo figlio!\n");
        return -1;
    } 
    
    else if (pid == 0) {
        // Codice del processo figlio
        char *pythonFile = newfile;
        
        if (execlp("python3", "python3", pythonFile, NULL) == -1) {
            printf("Errore nell'esecuzione del file Python.\n");
            return -1;
        }
    } 
    
    else {
        // Codice del processo padre
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            int exitStatus = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            int signalNumber = WTERMSIG(status);
        }
    }
    //da qui in poi puoi inserire tutto il resto del codice del processo padre, in C

    return 0;
}
