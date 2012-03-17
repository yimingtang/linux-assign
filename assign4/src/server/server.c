#include "fifo.h"
#include "common.h"
#include "transaction.h"

int main(int argc, const char *argv[])
{
    
    int listenfd = init_server();
    while(true) {
        listen_client(listenfd);
        start_service();
    }
    return 0;
}


