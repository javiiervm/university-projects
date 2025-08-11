// Shared mem: Libraries to handle shared memory
#include <sys/types.h>    // Defines data types used in system calls, e.g., pid_t
#include <sys/ipc.h>      // Defines macros and types used for inter-process communication (IPC)
#include <sys/shm.h>      // Defines shared memory-related functions and constants

// IO operations: Libraries for input/output operations
#include <stdio.h>        // Standard Input and Output, e.g., printf function

// Fork, exit etc.: Libraries to handle process creation and termination
#include <unistd.h>       // Contains functions for process control, e.g., fork(), getpid(), sleep()
#include <stdlib.h>       // Contains functions for memory allocation, process control, conversions, etc.

// Prints array: Function to print an integer array
void parray(int arr[], int size){
    // Loop to iterate through the array elements
    for (int i=0; i<size; i++){
        // Print each element in the array
        printf("%d", arr[i]);
        if (i!=(size-1))
            printf(", "); // Print a comma and space except for the last element
        else
            printf("\n"); // Print a newline character after printing the last element
    }
}

// Main function, where the program execution starts
int main(){
    // Id of the piece of shared memory that will be created
    int shmid=0;

    // Pointer that will point to the array inside the shared memory
    __pid_t *numero;

    // Initialize the pointer to NULL since it currently does not point to any valid memory address
    numero = NULL;

    int s=3;  // Size of the array we want to create (an array with 3 elements)

    /* Creates a piece of shared memory:
        - IPC_PRIVATE indicates that this memory will only be accessible to related processes (parent-child processes).
        - s * sizeof(__pid_t) specifies the size of the shared memory, which is equal to the size of 3 elements of type __pid_t.
        - IPC_CREAT | 0666 creates the shared memory segment with the given permissions (0666 means read and write permission for all users).
    */
    shmid = shmget(IPC_PRIVATE, s * sizeof(__pid_t), IPC_CREAT | 0666);
    if (shmid == -1){
        // Check if there was an error while creating the shared memory and print an error message
        printf("Error while creating shared memory\n");
        return 1;  // Return error code 1 if the shared memory cannot be created
    }

    // Attach the shared memory segment to the pointer "numero".
    // shmat returns the address of the shared memory and assigns it to "numero".
    numero = (__pid_t*) shmat(shmid, 0, 0);

    // Example of how to assign values to the array in shared memory
    numero[0] = getpid();  // Set the first element to the current process ID (PID)
    numero[1] = 2;         // Set the second element to 2
    numero[2] = 3;         // Set the third element to 3

    // Create a new process by forking the current process
    __pid_t pid = fork();

    // The fork() function creates a child process. The return value differs for parent and child:
    // - pid == -1: Error occurred during fork.
    // - pid == 0: This block runs in the child process.
    // - pid > 0 (default): This block runs in the parent process.
    switch (pid) {
        case -1:
            // If pid is -1, print an error message since fork() failed
            printf("ERROR\n");
            break;
        case 0:
            // This block is executed by the child process
            // Modify the value at index 1 of the shared memory array to the child's PID
            // Since it's shared memory, the changes made by the child will be visible to the parent process as well
            numero[1] = getpid(); 
            printf("\nI am the child (%d)\n", getpid());  // Print the child's PID
            break;
        default:
            // This block is executed by the parent process
            sleep(1);  // Delay to give the child process time to execute its code
            printf("\nI am the father(%d)\nNumero is: ", getpid());
            // Print the array to show the changes made by the child process
            // Since the child modified numero[1], it should now contain the child's PID instead of the value 2
            parray(numero, s);
            break;
    }

    // Detach the shared memory from the current process (both child and parent must do this).
    // The argument should be a character array, so we cast "numero" to a char*.
    if (shmdt((char*) numero) < 0) {
        // Print error message if detaching the shared memory fails
        printf("Error when unlinking memory\n");
        return 1;  // Return error code 1 if detachment fails
    }

    // Only the parent process should delete the shared memory.
    // If both processes try to delete it, it will cause an error.
    char error[100];
    if (pid != 0) {
        // The parent process deletes the shared memory
        // shmctl is used here to delete the memory (IPC_RMID option)
        if (shmctl(shmid, IPC_RMID, 0) < 0) {
            // If deletion fails, print an error message with the parent's PID
            sprintf(error, "Pid %d: Error al borrar memoria compartida:", getpid());
            perror(error);
            exit(4);  // Exit with error code 4
            return 1; // Return error code 1
        }
    } else if (pid == 0) {
        // Child process should exit after executing its code
        exit(0);
    }

    // Print a success message if everything finishes successfully
    printf("Everything finished successfully\n");
}