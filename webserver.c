/* webserver.c */

#include "webserver.h"

int create_socket()
{
    int server_fd;
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket fehlgeschlagen.");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void bind_socket(int server_fd, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
    {
        perror("Bindung zum Socket fehlgeschlagen.");
        exit(EXIT_FAILURE);
    }
}

void listen_socket(int server_fd)
{
    if(listen(server_fd, 3) < 0)
    {
        perror("Listening des Servers fehlgeschlagen.");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}

int accept_connection(int server_fd, struct sockaddr_in *addr)
{
    int addrlen = sizeof(*addr);
    int new_socket = accept(server_fd, (struct sockaddr *)addr, (socklen_t *)&addrlen);

    if(new_socket < 0)
    {
        perror("Accept failed.");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return new_socket;
}

void read_socket(int socket, char *buffer, size_t size)
{
    read(socket, buffer, size);
}

void write_socket(int socket, const char *response)
{
    write(socket, response, strlen(response));
}


int main()
{
    int server_fd, new_socket;
    struct sockaddr_in addr;
    char buffer[1024] = {0};
    const char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nMoin, Meister!";

    server_fd = create_socket();
    bind_socket(server_fd, &addr);
    listen_socket(server_fd);
    new_socket = accept_connection(server_fd, &addr);

    read_socket(new_socket, buffer, sizeof(buffer));
    printf("%s\n", buffer);

    write_socket(new_socket, message);
    printf("Nachricht wurde verschickt, Meister!");

    close(new_socket);
    close(server_fd); 

    return 0;
}
