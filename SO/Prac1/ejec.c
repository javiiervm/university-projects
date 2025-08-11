#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// This function checks if the received parameters in the program are correct. Returns false if there is any error, true otherwise
bool argCheck(int argc, char *argv[], int *seconds) {
    // Check that the number of parameters is correct, that is, 3 parameters (./ejec -s [seconds])
    if(argc != 2)
        return false;

    *seconds = atoi(argv[1]);  // Convert string to integer
    return true;
}

// Checks if the number of seconds is greater or equal to zero, returns true if it is correct, false otherwise
bool secondChecker(int seconds) {
    if(seconds<=0) {
        printf("ERROR: Seconds must be greater than zero!\n");
        return false;
    }
    return true;
}

// Handler for the SIGALRM signal in process Z
void handle_alarm(int sig) {
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);
            break;

        case 0:
            execlp("pstree", "pstree", "-p", NULL);  // Run pstree command
            perror("execlp failed");  // In case execlp fails
            exit(0);
            break;
        
        default:
            wait(NULL);  // Z waits for pstree child to finish
            break;
    }
}


void treeCreator(int seconds) {
    __pid_t pid, pidEjec = getpid(), pidA, pidB, pidX, pidY, pidZ;

    pid = fork();   // Fork for creating process A

    switch (pid) {  // Both 'Ejec' and 'A' enter this switch
        case -1:    // Error handling
            perror("ERROR: Couldn't create process A");
            exit(1);
            break;
        
        case 0:     // Child process 'A'
            pidA = getpid();  // Save process A's pid
            printf("I’m the process A: my pid is %d. My father is %d\n", pidA, getppid());

            pid = fork();   // Fork for creating process B

            switch (pid) {  // Both 'A' and 'B' enter this switch
                case -1:    // Error handling
                    perror("ERROR: Couldn't create process B");
                    exit(1);
                    break;

                case 0:     // Child process 'B'
                    pidB = getpid();
                    printf("I’m the process B: my pid is %d. My father is %d, grandfather %d\n", pidB, pidA, pidEjec);

                    pid = fork();   // Fork process 'X'
                    switch (pid) {
                        case -1:
                            perror("ERROR: Couldn't create process X");
                            exit(1);
                            break;

                        case 0: // Child process 'X'
                            pidX = getpid();
                            printf("I’m the process X: my pid is %d. My father is %d, grandfather %d, great-grandfather is %d\n", pidX, pidB, pidA, pidEjec);
                            sleep(seconds + 2);  // X waits to be terminated
                            printf("I am X and I die\n");
                            exit(0);
                            break;
                        
                        default:
                            break;
                    }

                    pid = fork();   // Fork process 'Y'
                    switch (pid) {
                        case -1:
                            perror("ERROR: Couldn't create process Y");
                            exit(1);
                            break;

                        case 0: // Child process 'Y'
                            pidY = getpid();
                            printf("I’m the process Y: my pid is %d. My father is %d, grandfather %d, great-grandfather is %d\n", pidY, pidB, pidA, pidEjec);
                            sleep(seconds + 1);  // Y waits to be terminated
                            printf("I am Y and I die\n");
                            exit(0);
                            break;
                        
                        default:
                            break;
                    }

                    pid = fork();   // Fork process 'Z'
                    switch (pid) {
                        case -1:
                            perror("ERROR: Couldn't create process Z");
                            exit(1);
                            break;

                        case 0: // Child process 'Z'
                            pidZ = getpid();
                            printf("I’m the process Z: my pid is %d. My father is %d, grandfather %d, great-grandfather is %d\n", pidZ, pidB, pidA, pidEjec);

                            // Set the alarm for process Z
                            signal(SIGALRM, handle_alarm);  // Set up the alarm signal handler
                            alarm(seconds);  // Schedule an alarm after the specified number of seconds
                            pause();  // Z waits for the alarm signal

                            // After alarm (and pstree) run, terminate other processes
                            printf("I am Z and I die\n");
                            exit(0);
                            break;
                        
                        default:
                            break;
                    }

                    // Parent process B waits for all children (X, Y, Z) to terminate
                    wait(NULL);  // Wait for Z
                    wait(NULL);  // Wait for Y
                    wait(NULL);  // Wait for X
                    printf("I am B and I die\n");
                    exit(0);
                    break;
                
                default:    // Parent process A waits for B to terminate
                    wait(NULL);
                    printf("I am A and I die\n");
                    exit(0);
                    break;
                }

        default:    // Parent process 'Ejec'
            printf("I'm the process ejec: my pid is %d\n", getpid());
            wait(NULL);  // Wait for A to terminate
            printf("I am ejec and I die\n");
            break;
    }
}

int main(int argc, char *argv[]) {
    // Local variables
    int seconds = 0;

    // Check if the received parameters are correct
    if(!argCheck(argc, argv, &seconds)) {
        printf("ERROR: Wrong input parameters, must be ./ejec [seconds]!\n");
        return -1;  // If there is any problem with the parameters, finish the program with error code -1
    }

    // Check if the seconds are correct
    if(!secondChecker(seconds))
        return -1;

    treeCreator(seconds);  // Calls the function that creates the tree

    return 0;
}