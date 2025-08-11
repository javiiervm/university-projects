#include <sys/socket.h>       // Socket functions
#include <netinet/in.h>       // For sockaddr_in structure
#include <arpa/inet.h>        // For IP address manipulation functions
#include <stdio.h>            // Standard I/O functions
#include <stdlib.h>           // Standard library functions
#include <unistd.h>           // POSIX API, including read() and close()
#include <string.h>           // String manipulation functions
#include <sys/types.h>        // Data types for socket functions
#include <sys/wait.h>         // For wait() function
#include <stdbool.h>          // For true and false

#define PORT 9999
#define HISTORY_FILE "history.txt"

int main() {
    int listenfd = 0, connfd = 0;             // Socket descriptors: listenfd for listening, connfd for client connection
    struct sockaddr_in serv_addr;             // Structure to hold the server's address information
    char sendBuff[1024];                      // Buffer to store data to send to the client
    char recvBuff[1024];                      // Buffer to store data received from client
    pid_t pid;                                // PID for child process
    bool finishConnection = false;            // Signal to end the connection

    int pipefd[2];                            // Pipe for IPC between parent and child processes
    pipe(pipefd);                             // Create a pipe; pipefd[0] for reading, pipefd[1] for writing

    // Initialize the server socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr)); // Clear serv_addr to zero to prevent garbage values
    memset(sendBuff, '\0', sizeof(sendBuff));   // Clear sendBuff

    serv_addr.sin_family = AF_INET;             // Set address family to IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP
    serv_addr.sin_port = htons(PORT);           // Set the port to 9999, as specified

    // Bind the socket to the specified IP and port
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Start listening for incoming connections, with a backlog of 10
    listen(listenfd, 10);

    printf("Server connected on port %d\n", PORT);
    printf("Waiting for client...\n");

    while(1) {
        if (finishConnection) {
            break;
        }

        // Accept a client connection, connfd will be the new socket for this client
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        printf("Connected to client\n\n");

        // Open the history file for appending commands
        FILE *historyFile = fopen(HISTORY_FILE, "a+");
        if (historyFile == NULL) {
            perror("Error: Could not open history file\n");
            close(connfd);
            continue;
        }

        // Fork a new process to handle the client connection
        pid = fork();
        if (pid < 0) {
            // Error handling if fork fails
            perror("Error: Couldn't create child process\n");
            close(connfd); // Close connection descriptor on error
            fclose(historyFile);
            continue;
        }

        if (pid == 0) { // Child process block
            close(listenfd); // Child doesn’t need the listening socket
            close(pipefd[0]); // Close reading end of the pipe in the child process

            while(1) {
                memset(recvBuff, '\0', strlen(recvBuff));
                memset(sendBuff, '\0', strlen(sendBuff));
                int n = read(connfd, recvBuff, sizeof(recvBuff) - 1);

                if (n > 0) {
                    recvBuff[n] = '\0'; // Null-terminate received data

                    // Write received command to history file
                    fprintf(historyFile, "%s\n", recvBuff);
                    fflush(historyFile); // Ensure data is written immediately

                    if (strcmp(recvBuff, "END") == 0) {
                        // Notify parent and exit if command is "END"
                        printf("Ending session with client.\n");
                        write(pipefd[1], "1", 1); // Notify parent
                        break;
                    } else if (strcmp(recvBuff, "history") == 0) {
                        printf("Executing command '%s'...\n", recvBuff);

                        // Use the "cat history.txt" command to display history
                        FILE *command = popen("cat " HISTORY_FILE, "r");
                        if (command == NULL) {
                            perror("Error executing history command");
                            break;
                        }

                        // Send command output to client
                        while (fgets(sendBuff, sizeof(sendBuff), command) != NULL) {
                            write(connfd, sendBuff, strlen(sendBuff)); // Send output line by line
                        }
                        pclose(command); // Close the command pipe after execution
                        printf("History displayed successfully.\n\n");
                    } else {
                        // Execute other commands using popen()
                        FILE *command = popen(recvBuff, "r");
                        if (command == NULL) {
                            perror("Error executing command");
                            break;
                        }

                        printf("Executing command '%s'...\n", recvBuff);

                        // Send command output to client
                        while (fgets(sendBuff, sizeof(sendBuff), command) != NULL) {
                            write(connfd, sendBuff, strlen(sendBuff)); // Send output line by line
                        }
                        pclose(command); // Close the command pipe after execution
                        printf("Command executed successfully.\n\n");
                    }
                } else if (n == 0) {
                    // Client closed the connection
                    printf("Client disconnected.\n");
                    break;
                } else {
                    perror("Error reading from client");
                    break;
                }
            }

            close(pipefd[1]); // Close the writing end of the pipe
            close(connfd);     // Close client socket in child process
            fclose(historyFile); // Close history file in child
            exit(0);           // Exit child process
        } else {
            // Parent process block
            close(connfd);       // Close client socket in parent process
            close(pipefd[1]);    // Close writing end of the pipe in parent

            // Check if the child sent a message to terminate
            char pipeMsg;
            if (read(pipefd[0], &pipeMsg, 1) > 0) {
                // Set finishConnection to true if the "END" command was received
                finishConnection = true;
                printf("Shutting down server...\n");

                // Delete the history file after "END" command
                if (remove(HISTORY_FILE) == 0) {
                    printf("History file deleted successfully.\n");
                } else {
                    perror("Error deleting history file\n");
                }
            }
        }
    }

    // Clean up and close server
    close(pipefd[0]); // Close reading end of the pipe in the parent
    close(listenfd);  // Close the listening socket
    return 0;
}
