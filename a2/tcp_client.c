#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024], response[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.0.0.1"); // server IP (h1)

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter fruit name and quantity: ");
    fgets(buffer, sizeof(buffer), stdin);

    send(sock, buffer, strlen(buffer), 0);

    read(sock, response, sizeof(response));
    printf("\nServer Response:\n%s\n", response);

    close(sock);
    return 0;
}
