#ifndef CONNECTION_H
#define CONNECTION_H

#include "common.h"
#include "defs.h"

bool send_request(request_type type, int param_num, char *params[]);
bool send_response(response_status status, int rs_len, char *rs);
response * recv_response();
request * recv_request();

#endif
