#ifndef DEFS_H
#define DEFS_H


typedef int bool;
#define true    1;
#define false   0;

#define MAX_PARAMS_NUM 5;

typedef enum {
    SUCCESS,
    FAILED,
} response_status;

typedef enum {
    REGISTER,
    LOGIN,
    QUERY,
    ORDER,
    DISCONNET,
} request_type;

typedef struct _request {
    request_type type;
    int param_num;
    char *params[MAX_PARAMS_NUM];
} request;

typedef struct _reponse {
    response_status status;
    char *result;
    int rs_len;
} reponse;

#endif
