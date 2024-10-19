#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(servaddr);
    
    while (1) {
        char message[BUFFER_SIZE];

        // Prompt the user for input
        printf("Enter message to send (or 'exit' to quit): ");
        fgets(message, BUFFER_SIZE, stdin);

        // Remove newline character from message
        message[strcspn(message, "\n")] = 0;

        // Check for exit condition
        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Send message to server (without MSG_CONFIRM flag)
        sendto(sockfd, (const char *)message, strlen(message), 0, (const struct sockaddr *)&servaddr, len);
        printf("Message sent to server: %s\n", message);

        // Receive response from server
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
