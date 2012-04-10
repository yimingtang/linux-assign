#include "connection.h"
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>




FILE *read_file;
FILE *write_file;

static response resp;
static request req; 

#define BUFF_SIZE 1024

char buffer[BUFF_SIZE];

bool send_request(request_type type, int param_num, char *params[])
{
    fprintf(write_file, "%d %d ", type, param_num);
    int i;
    for (i = 0; i < param_num; i++) {
        fprintf(write_file, "%s ", params[i]);
    }
    fflush(write_file);
    return true;
}

bool send_response(response_status status, int rs_len, char *rs)
{
    fprintf(write_file, "%d %d ", status, rs_len);
    fwrite(rs, sizeof(char), rs_len, write_file);
    fflush(write_file);
    return 0;
}

response * recv_response()
{
    int status;
    // free resp
    if (resp.rs_len > 0) {
        free(resp.result);
    }   
    fscanf(read_file, "%d", &status); 
    resp.status= (response_status)status;
    fscanf(read_file, "%d", &(resp.rs_len)); 
    if (resp.rs_len > 0) {
        resp.result = (char *)(malloc(sizeof(char) * resp.rs_len));
        fread(resp.result, sizeof(char), resp.rs_len, read_file);
        resp.result[resp.rs_len] = '\0';
    }
    __fpurge(read_file);
    return &resp;
}

request * recv_request()
{
    char * buf_ptr = buffer;
    int type;
    memset(buffer, 0, sizeof(buffer));
    fscanf(read_file, "%d", &type);
    req.type = (request_type)type;
    fscanf(read_file, "%d", &req.param_num);
    int i;
    for (i = 0; i < req.param_num; i++) {
        req.params[i] = buf_ptr;
        fscanf(read_file, "%s", buf_ptr);
        buf_ptr = buf_ptr + strlen(buf_ptr) + 1;
    }
    __fpurge(read_file);
    return &req;
}
