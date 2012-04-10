#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "error.h"
#include "connection.h"
#include "fifo.h"

static int dummy_fifo;


int init_server() {
    int public_fifo_fd;
    //make fifo
    if ((mkfifo(SERVER_FIFO_NAME, FIFO_MODE) < 0) && (errno != EEXIST))
        error_exit(1, "create fifo failed.", NULL);
    // read fd
    if ((public_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY, 0)) == -1)
        error_exit(1, "open file failed", NULL);
    // write fd: a dummy fd
    if ((dummy_fifo = open(SERVER_FIFO_NAME, O_WRONLY, 0)) == -1)
        error_exit(1, "open file failed", NULL);
    write_file = NULL;
    write_file = NULL;
    return public_fifo_fd;
}


int connect_server() {
    char buf[HELLO_LEN];
    char name_r[NAME_LEN];
    char name_w[NAME_LEN];

    fprintf(stderr, "make fifos...\n");
    int pid = getpid();
    //make two fifos
    sprintf(name_r, CLIENT_FIFO_NAME_R, pid);
    if ((mkfifo(name_r, FIFO_MODE) < 0) && (errno != EEXIST))
        error_exit(1, "create fifo failed.", NULL);

    sprintf(name_w, CLIENT_FIFO_NAME_W, pid);
    if ((mkfifo(name_w, FIFO_MODE) < 0) && (errno != EEXIST))
        error_exit(1, "create fifo failed.", NULL);

    fprintf(stderr, "fifo:  %s\n%s\n",name_r,name_w);

    // open public fifo, say hello to server with a pid
    int public_fifo_fd;
    if ((public_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY, 0)) == -1)
          error_exit(1, "open file failed", NULL);
    sprintf(buf, "%d\n", (int)getpid());
    write(public_fifo_fd, buf, HELLO_LEN); 
    //close public fifo fd.
    if (close(public_fifo_fd) == -1)
        error_exit(1, "close file error" ,NULL);

    fprintf(stderr, "opening read_file...\n");
    read_file = fopen(name_r, "r");
    fprintf(stderr, "waiting for server...\n");
    fscanf(read_file, "%s", buf);
    fprintf(stderr, "server msg: %s\n",buf );


    write_file = fopen(name_w, "w");
    fprintf(stderr, "send to server...\n");
    fprintf(write_file, "hello,server\n");
    fflush(write_file);

    return 0;
}

int listen_client(int fd) {
    char buf[HELLO_LEN];
    char name_r[NAME_LEN];
    char name_w[NAME_LEN];
    int size;
    if (read_file || write_file) {
        fclose(read_file);
        fclose(write_file);
    }
    
    //waiting for request
    fprintf(stderr, "server process id: %ld\nstatus: waiting...\n", (long)getpid());
    if((size = read(fd, buf, sizeof(buf) ) == -1))
        error_exit(1, "can't read file",NULL);
    fprintf(stderr, "server process id: %ld\nstatus: running...\n", (long)getpid());

    // buf[size-1] = '\0';
    fprintf(stderr,"client pid: %s\n",buf);
    int pid = atoi(buf);
    fprintf(stderr,"client pid again: %d\n",pid);

    //open fifo fd
    sprintf(name_r, CLIENT_FIFO_NAME_W, pid);
    sprintf(name_w, CLIENT_FIFO_NAME_R, pid);

    
    write_file = fopen(name_w, "w");
    //set confirm
    fprintf(stderr, "try to write...\n");
    fprintf(write_file, "hello,client\n"); 
    fflush(write_file);

    read_file = fopen(name_r, "r");
    fscanf(read_file, "%s", buf);
    fprintf(stderr, "msg from client: %s\n", buf);
    return 0;
} 



int close_connect() {
  fclose(read_file);
  fclose(write_file);
  fprintf(stderr, "close connection\n" );
  return 0;
}