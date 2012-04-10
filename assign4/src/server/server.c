//#include "fifo.h"
#include <unistd.h>
#include <stdio.h>
#include "socket.h"
#include "common.h"
#include "transaction.h"


int main(int argc, const char *argv[])
{
    int listen_fd, new_fd;
    listen_fd = init_server();  // init server, listen
    while (true) {
        new_fd = accept_client(listen_fd);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        /*
         * if accepted, fork()
         */
        if (!fork()) { // this is the child process
            close(listen_fd); // child doesn't need the listener
            if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            bind_file(new_fd);
            start_service();
            close_connection();
            close(new_fd);
            exit(0);
        }
        close(new_fd);  
    }
    return 0;
}


