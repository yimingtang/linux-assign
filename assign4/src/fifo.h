#ifndef FIFO_H
#define FIFO_H

#define SERVER_FIFO_NAME    "/tmp/serv_fifo"
#define CLIENT_FIFO_NAME    "/tmp/cli_%d_fifo"
#define FIFO_MODE 0777

/*
 * init server fifo, create public fifo
 */
int init_server();

/*
 * connect to the server, and dup file descriptors
 */
int connect_client();
/*
 * setup connection between client and server, dup file descriptors
 */
int connect_server();
/*
 *close file discriptors
 */
int close_connect();

#endif
