#include "fifo.h"
#include "common.h"

int main(int argc, const char *argv[])
{
    
    int listenfd = init_server();
    while(true) {
        listen_client(listenfd);
    }
    return 0;
}


