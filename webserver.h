/* webserver.h */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// create socket
int create_socket();

// bind socket to addr
void bind_socket(int server_fd, struct sockaddr_in *addr);

// listen to incoming connection
void listen_socket(int server_fd);

// accecpt incoming connection
int accept_connection(int server_fd, struct sockaddr_in *addr);

// reading data from socket
void read_socket(int socket, char *buffer, size_t size);

// send data to socket
void write_socket(int socket, const char *response);

#endif WEBSERVER_H