#ifndef SOCKET_H
#define SOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define PORT "3000"
#define BACKLOG 10
#define HOSTNAME "localhost"
#define MAXDATASIZE 512
/*
 *
 * init server, setup socket
 */
int init_server();

/* server listen to client 
 * accept and connect
 */
int accept_client(int listen_fd);

/*
 * bind the accepted file descriptor to read_file and write_file
 */
void bind_file(int new_fd);

/* 
 * client connect  server
 */
int connect_server();

/*
 * close the connection 
 */
int close_connection();

#endif
