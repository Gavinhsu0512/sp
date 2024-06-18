#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define THREAD_POOL_SIZE 10

#pragma comment(lib, "ws2_32.lib")

typedef struct {
    struct sockaddr_in client_addr;
    SOCKET client_socket;
} client_t;

void *handle_request(void *client_ptr) {
    client_t *client = (client_t *)client_ptr;
    char buffer[BUFFER_SIZE];
    int read_size = recv(client->client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (read_size > 0) {
        buffer[read_size] = '\0';
        printf("Received request: %s\n", buffer);

        char response[] = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/plain\r\n"
                          "Content-Length: 12\r\n"
                          "\r\n"
                          "Hello World!";
        send(client->client_socket, response, sizeof(response) - 1, 0);
    }

    closesocket(client->client_socket);
    free(client);
    return NULL;
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    // 初始化 Winsock
    printf("\nInitializing Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Initialized.\n");

    // 創建伺服器套接字
    if((server_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 綁定伺服器套接字
    if (bind(server_socket, (struct sockaddr *)&server_addr , sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    printf("Bind done.\n");

    // 監聽連接
    listen(server_socket, 10);
    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            printf("accept failed with error code : %d" , WSAGetLastError());
            continue;
        }

        client_t *client = (client_t *)malloc(sizeof(client_t));
        client->client_addr = client_addr;
        client->client_socket = client_socket;

        pthread_t thread;
        pthread_create(&thread, NULL, handle_request, (void *)client);
        pthread_detach(thread);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
