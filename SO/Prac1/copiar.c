#include <stdio.h>
#include <stdbool.h>
#include <string.h>     // For strcmp
#include <stdlib.h>     // For atoi
#include <unistd.h>     // For calls
#include <sys/wait.h>   // For wait() function
#include <fcntl.h>      // For open() function

// This function checks if the received parameters in the program are correct. Returns false if there is any error, true otherwise
bool argCheck(int argc, char *argv[]) {
    // Check that the number of parameters is correct, that is, 3 parameters (./copiar origen.txt destino.txt)
    if(argc != 3)
        return false;
    return true;
}

// This function
bool copyFile(char *origen, char *destino) {
    int readfile, writefile;

    int fd[2];  // fd[0] = read; fd[1] = write;
    if(pipe(fd)==-1) {
        printf("An error ocurred creating the pipe\n");
        return false;
    }

    __pid_t pid = fork();

    switch (pid) {
        case -1: // Error handling
            printf("ERROR: Couldn't create the process\n");
            exit(1); // Error code
            break;

        case 0:
            close(fd[1]);
            writefile = open(destino, O_WRONLY | O_CREAT, 0644);
            if (writefile != -1) {
                char buffer[256];
                ssize_t nbytes;
                while ((nbytes = read(fd[0], buffer, sizeof(buffer))) > 0)
                    write(writefile, buffer, nbytes);
            }
            close(fd[0]);
            close(writefile);
            break;
        
        default:
            readfile = open(origen, O_RDONLY);
            if (readfile != -1) {
                char buffer[256];
                ssize_t nbytes;
                while ((nbytes = read(readfile, buffer, sizeof(buffer))) > 0) {
                    write(fd[1], buffer, nbytes);
                }
            }
            close(fd[1]);
            close(readfile);

            // Wait for child process to finish
            wait(NULL);
            break;
    }

    sleep(3);
    return true;
}

// Main function of the program
int main(int argc, char *argv[]) {
    // Check if the received parameters are correct
    if(!argCheck(argc, argv)) {
        printf("ERROR: Wrong input parameters, must be ./copiar origen.txt destino.txt\n");
        return -1;  // If there is any problem with the parameters, finish the program with error code -1
    }

    if(!copyFile(argv[1], argv[2]))
        return 1;

    return 0;
}
