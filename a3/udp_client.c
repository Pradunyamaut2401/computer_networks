#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024], response[1024];
    socklen_t addr_len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.1"); // h1 IP

    printf("Enter fruit name and quantity: ");
    fgets(buffer, sizeof(buffer), stdin);

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&server_addr, addr_len);

    recvfrom(sockfd, response, sizeof(response), 0,
             (struct sockaddr *)&server_addr, &addr_len);

    printf("\nServer Response:\n%s\n", response);

    close(sockfd);
    return 0;
}
