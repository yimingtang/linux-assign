#include "core.h"
#include "fifo.h"

int main(int argc, const char *argv[])
{
	connect_server();
	start_client();
	close_connect();
    return 0;
}



