#include <stdio.h>
#include <stdbool.h>
#include <string.h>     // For strcmp
#include <stdlib.h>     // For atoi (to convert arguments to integers)
#include <unistd.h>     // For fork() (to create child processes)
#include <sys/wait.h>   // For wait() (to wait for child processes)
#include <sys/shm.h>    // For shared memory functions

// Function to check if received parameters are correct.
// Returns false if there is any error, true otherwise.
// Converts the arguments to integers x and y.
bool argCheck(int argc, char *argv[], int *x, int *y) {
    if (argc != 3) {  // Check if the number of arguments is correct (program name + 2 arguments)
        return false; // Return false if arguments are incorrect
    }

    *x = atoi(argv[1]);  // Convert the first argument to an integer (number of child processes)
    *y = atoi(argv[2]);  // Convert the second argument to an integer (number of subchild processes)

    return true; // Return true if arguments are correct
}

// Function to create the process tree
bool treeCreator(int x, int y) {
    // Local variables
    __pid_t pid;
    int shmid;  // Id of the piece of shared memory that will be created
    __pid_t *pidList;   // Pointer that will point to the vector inside the shared memory

    // Create shared memory to store PIDs of the processes
    /*
        - IPC_PRIVATE indicates that this memory will only be accessible to related processes (parent-child processes).
        - s*sizeof(__pid_t) specifies the size of the shared memory, which is equal to the size of x + y + 1 elements of type __pid_t.
        - IPC_CREAT | 0666 creates the shared memory segment with the given permissions (0666 means read and write permission for all users).
    */
    shmid = shmget(IPC_PRIVATE, (x + y + 1)*sizeof(__pid_t), IPC_CREAT | 0666);
    if (shmid == -1){   // Check if there was an error while creating the shared memory and print an error message
        printf("Error while creating shared memory\n");
        return false;  // Return error if the shared memory cannot be created
    }

    // Attach the shared memory segment to the pointer "pidList".
    // shmat returns the address of the shared memory and assigns it to "pidList".
    pidList = (__pid_t*) shmat(shmid, NULL, 0);
    if (pidList == (__pid_t*) -1) {   // Check if there was an error while attaching the shared memory and print an error message
        perror("ERROR: Couldn't attach shared memory\n");
        exit(1);
    }

    pidList[0] = getpid();  // Store the superfather's PID at index 0

    // Create x child processes (level 1 of the tree)
    for (int i = 1; i <= x; i++) {
        pid = fork();  // Create child process
        switch (pid) {
            case -1:    // Error case
                perror("ERROR: Couldn't create process\n");
                exit(1);  // Exit if fork fails
                break;

            case 0:     // Inside child process
                pidList[i] = getpid();  // Store the current child's PID
                if (i == x) {  // Last child has to have more child processes
                    for (int j = 1; j <= y; j++) {
                        pid = fork();
                        switch (pid) {
                            case -1:    // Error case
                                perror("ERROR: Couldn't create subchild process\n");
                                exit(1);  // Exit if fork fails
                                break;

                            case 0:     // Inside subchild process
                                pidList[x + j] = getpid();  // Store the subchild's PID
                                printf("I am the subchild %d, my parents are: ", getpid());
                                for (int k = 0; k <= x; k++) {
                                    printf("%d", pidList[k]);
                                    if (k < x && pidList[k+1]!=0 && pidList[k+1]!=getpid())
                                        printf(", ");
                                    else
                                        break;
                                }
                                printf("\n");
                                exit(0);  // Subchild process exits after printing its message
                                break;
                            
                            default:    // Inside parent process
                                wait(NULL);  // Parent waits for each subchild to finish
                                break;
                        }
                    }
                }
                exit(0);  // Child process exits after creating subchildren
                break;
            
            default:    // Inside parent process
                wait(NULL);  // Parent waits for each child to finish
                break;
        }
    }

    if (getpid() == pidList[0]) {   // In the superparent process, print information about the final children
        printf("I am the superfather (%d), my final children are: ", getpid());
        for (int i = x + 1; i <= x + y; i++) {
            printf("%d", pidList[i]);
            if (i < x + y)
                printf(", ");
        }
        printf("\n");
    }

    // Only one process can destroy the shared memory (otherwise an error appears), and it will be the parent
    if (getpid() == pidList[0]) {
        // Detach shared memory from the superfather process
        if (shmdt(pidList) == -1) {
            perror("ERROR: Couldn't detach shared memory\n");
            exit(1);
        }

        // Destroy the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("ERROR: Couldn't destroy shared memory\n");
            exit(1);
        }
    }

    return true;
}

// Main function of the program
int main(int argc, char *argv[]) {
    int x = 0, y = 0;

    // Check if the received parameters are correct
    if (!argCheck(argc, argv, &x, &y)) {
        printf("ERROR: Wrong input parameters, must be ./hijos x y\n");
        return -1;
    }

    // Create the process tree with given parameters
    if (!treeCreator(x, y))
        return -2;

    return 0;
}