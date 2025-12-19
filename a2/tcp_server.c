#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 9090
#define MAX_CLIENTS 50

struct Fruit {
    char name[20];
    int quantity;
    char last_sold[50];
};

struct Client {
    char ip[INET_ADDRSTRLEN];
    int port;
};

struct Fruit fruits[] = {
    {"apple", 10, "Never"},
    {"banana", 15, "Never"},
    {"orange", 8, "Never"}
};

struct Client clients[MAX_CLIENTS];
int client_count = 0;

int is_unique_client(char *ip, int port) {
    for (int i = 0; i < client_count; i++) {
        if (strcmp(clients[i].ip, ip) == 0 && clients[i].port == port)
            return 0;
    }
    strcpy(clients[client_count].ip, ip);
    clients[client_count].port = port;
    client_count++;
    return 1;
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Fruit Store Server running...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);

        is_unique_client(client_ip, client_port);

        read(client_fd, buffer, sizeof(buffer));

        char fruit_name[20];
        int req_qty;
        sscanf(buffer, "%s %d", fruit_name, &req_qty);

        char response[1024];
        int found = 0;

        for (int i = 0; i < 3; i++) {
            if (strcmp(fruits[i].name, fruit_name) == 0) {
                found = 1;
                if (fruits[i].quantity >= req_qty) {
                    fruits[i].quantity -= req_qty;

                    time_t now = time(NULL);
                    strcpy(fruits[i].last_sold, ctime(&now));

                    sprintf(response,
                        "Transaction successful!\nFruit Stock: %s = %d\nLast Sold: %s\nUnique Customers: %d\n",
                        fruits[i].name, fruits[i].quantity,
                        fruits[i].last_sold, client_count);
                } else {
                    sprintf(response,
                        "Regret! Insufficient stock.\nAvailable %s = %d\nUnique Customers: %d\n",
                        fruits[i].name, fruits[i].quantity, client_count);
                }
            }
        }

        if (!found) {
            sprintf(response, "Fruit not available.\nUnique Customers: %d\n", client_count);
        }

        send(client_fd, response, strlen(response), 0);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
