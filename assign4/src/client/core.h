#ifndef CORE_H
#define CORE_H
#include "common.h"

typedef enum
{  
	S_INIT,
	S_LOGIN,
	S_REGISTER,
	S_VERIFIED,
	S_ORDER,
	S_QUERY,
	S_EXIT,
	S_QUERY_ORDER
}C_Status;

void start_client();

#endif
