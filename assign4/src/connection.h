#ifndef CONNECTION_H
#define CONNECTION_H

#include "common.h"
#include "defs.h"
#include <stdio.h>

/*
 * client: send request
 */
bool send_request(request_type type, int param_num, char *params[]);

/*
 * server: send response
 */
bool send_response(response_status status, int rs_len, char *rs);

/*
 * server: receive response
 */
response *recv_response();

/*
 * client: receive request
 */
request *recv_request();

/* 
 * Both of the client and server hold these two file 
 * readonly and writeonly
 */
extern FILE *read_file;
extern FILE *write_file;

#endif
