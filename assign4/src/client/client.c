#include "core.h"
//#include "fifo.h"
#include "socket.h"

int main(int argc, const char *argv[])
{
    int sockfd = connect_server();
    start_client();
    close_connection();
    close(sockfd);
    return 0;
}



