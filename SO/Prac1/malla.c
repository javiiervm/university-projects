#include <stdio.h>
#include <stdbool.h>
#include <string.h>     // For strcmp
#include <stdlib.h>     // For atoi
#include <unistd.h>     // For calls
#include <sys/wait.h>   // For wait() function

// This function checks if the received parameters in the program are correct. Returns false if there is any error, true otherwise
bool argCheck(int argc, char *argv[], int *x, int *y) {
    // Check that the number of parameters is correct, that is, 5 parameters (./malla -x [value] -y [value])
    if(argc != 5)
        return false;

    // Check that the first parameter is -x, if it is, assign its value to the x variable
    if(strcmp(argv[1], "-x") != 0)
        return false;
    else
        *x = atoi(argv[2]);  // Convert string to integer

    // Check that the third parameter is -y, if it is, assign its value to the y variable
    if(strcmp(argv[3], "-y") != 0)
        return false;
    else
        *y = atoi(argv[4]);  // Convert string to integer

    return true;
}

// This function receives the rows and columns as parameters and creates the process tree
void treeCreator(int x, int y) {
    __pid_t pid = fork();  // Creation of the parent process with fork();

    for(int i = 1; i < y; i++) {  // Loop to create the columns
        if(pid!=0)
            pid = fork();
    }

    switch (pid) {
        case -1: // Error handling
            printf("ERROR: Couldn't create the process");
            exit(1); // Error code
            break;

        case 0:
            for(int i = 1; i < x; i++) {  // Loop to create the rows
                if (pid==0)
                    pid = fork();
            }
            break;
        
        default:
            break;
    }

    sleep(5);
}

// Main function of the program
int main(int argc, char *argv[]) {
    // Local variables
    int x = 0, y = 0;   // x = rows; y = columns

    // Check if the received parameters are correct
    if(!argCheck(argc, argv, &x, &y)) {
        printf("ERROR: Wrong input parameters, must be ./malla -x [value] -y [value]!\n");
        return -1;  // If there is any problem with the parameters, finish the program with error code -1
    }

    treeCreator(x, y);  // Calls the function that creates the tree

    return 0;
}
