#ifndef DEFS_H
#define DEFS_H

#define MAX_PARAMS_NUM 5

typedef enum {
    SUCCESS,
    FAILED,
} response_status;

typedef enum {
    REGISTER,
    LOGIN,
    QUERY,
    ORDER,
    DISCONNECT,
    QUERY_ORDER,
    LIST_ALL
} request_type;

/*
 * 1. check the type of request;
 * 2. get the number of params;
 * 3. read params;
 */
typedef struct _request {
    request_type type;
    int param_num;
    char *params[MAX_PARAMS_NUM];
} request;

/*
 * all responses have a status code and a result 
 */
typedef struct _response {
    response_status status;
    char *result;
    int rs_len;
} response;

#endif
