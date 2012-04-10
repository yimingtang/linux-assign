#ifndef FIFO_H
#define FIFO_H

#define SERVER_FIFO_NAME    "/tmp/fifo/serv_fifo"
#define CLIENT_FIFO_NAME_R   "/tmp/fifo/cli_%d_fifo_r"
#define CLIENT_FIFO_NAME_W  "/tmp/fifo/cli_%d_fifo_w"
#define FIFO_MODE 0777

#define HELLO_LEN 16 
#define NAME_LEN 32

/*
 * init server fifo, create public fifo
 */
int init_server();

/*
 * listen on public fifo, if there's a connection, set up
 */
int listen_client(int fd);

/*
 * setup connection between client and server, dup file descriptors
 */
int connect_server();
/*
 *close file discriptors
 */
int close_connect();

#endif
