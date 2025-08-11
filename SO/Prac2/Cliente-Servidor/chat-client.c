#include <sys/socket.h>       // Socket functions
#include <netinet/in.h>       // For sockaddr_in structure
#include <arpa/inet.h>        // For IP address manipulation
#include <stdio.h>            // Standard I/O functions
#include <string.h>           // String manipulation functions
#include <stdlib.h>           // Standard library functions
#include <unistd.h>           // POSIX API, including read() and close()
#include <errno.h>            // Error handling macros

#define PORT 9999

int main(int argc, char *argv[]) {
    int sockfd = 0, n = 0;              // Socket descriptor and variable for read result
    char recvBuff[1024];                // Buffer to store data received from server
    char sendBuff[1024];                // Buffer to send data to the server
    struct sockaddr_in serv_addr;       // Server address structure

    // Verify correct usage with IP address as argument
    if (argc != 2) {
        printf("\nUsage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    // Initialize receive buffer and socket
    memset(recvBuff, '0', sizeof(recvBuff));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error: Could not create socket");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // Clear server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);           // Connect to port 9999 as specified

    // Convert the IP address from text to binary and store in serv_addr.sin_addr
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Error: Invalid address format");
        return 1;
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error: Connect Failed");
        return 1;
    }

    printf("Succesfully connected to port %d\nEnter any command (or 'END' to quit)\n\n", serv_addr.sin_port);
    printf("=============== [CONNECTED TO SERVER: IP %s] ===============", argv[1]);

    while (1) {
        // Prompt user for a command
        printf("\n>> ");
        fgets(sendBuff, sizeof(sendBuff), stdin);
        sendBuff[strcspn(sendBuff, "\n")] = '\0';  // Remove trailing newline from fgets

        // Send command to the server
        write(sockfd, sendBuff, strlen(sendBuff));

        // Check for "END" command to break loop and close connection
        if (strcmp(sendBuff, "END") == 0) {
            printf("Ending session.\n");
            break;
        }

        // Read and print the server's response until no more data is available
        while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0) {
            recvBuff[n] = '\0'; // Null-terminate the data
            printf("%s", recvBuff); // Print received data to console
            if (n < sizeof(recvBuff) - 1) break; // Break if all data was received
        }

        if (n < 0) {
            perror("Read error");
        }
    }

    // Close the socket after the communication ends
    close(sockfd);
    return 0;
}