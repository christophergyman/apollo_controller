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
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(cliaddr);  // Length of the client address
    int n;

    while (1) {
        // Receive message from client
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);

        // Check for exit condition
        if (strcmp(buffer, "exit") == 0) {
            printf("Client has exited. Stopping server.\n");
            break;
        }

        // Send response to client
        char *response = "Hello from server";  // Customize the response message as needed
        sendto(sockfd, (const char *)response, strlen(response), 0, (const struct sockaddr *)&cliaddr, len);
        printf("Message sent to client: %s\n", response);
    }

    close(sockfd);
    return 0;
}
