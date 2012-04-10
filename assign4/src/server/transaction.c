#include "transaction.h"
#include "defs.h"
#include "connection.h"
#include "common.h"
#include "database.h"
#include <string.h>
#include <stdlib.h>

static void handle_login(request * req);
static void handle_register(request * req);
static void handle_order(request * req);
static void handle_query(request * req);
static void handle_query_orders(request * req);
static void handle_list_all_tickets(request * req);
static void handle_exit();

int start_service() {
  connect_db();
  while (true) {
    request * req = recv_request();
    switch(req->type) {
        case LOGIN:
            handle_login(req);
            break;
        case REGISTER:
            handle_register(req);
            break;
        case DISCONNECT:
            handle_exit();
            return 0;
        case QUERY:
            handle_query(req);
            break;
        case QUERY_ORDER:
            handle_query_orders(req);
            break;
        case LIST_ALL:
            handle_list_all_tickets(req);
            break;
        case ORDER:
            handle_order(req);
            break;
        default:
            break;
    }
  }
  return 0;
}

static void handle_login(request * req)
{
    bool rs = has_user(req->params[0], req->params[1]);
    response_status status = FAILED;
    if (rs) 
      status = SUCCESS;
    send_response(status, 0, NULL);
}

static void handle_register(request * req)
{
    fprintf(stderr, "username: %s\npassword: %s\n", req->params[0],req->params[1] );
    bool rs = db_register(req->params[0], req->params[1]);
    response_status status = FAILED;
    if(rs == true)
        status = SUCCESS;
    send_response(status, 0, NULL);
}


static void handle_order(request * req)
{
    int status;
    int ticket_id = atoi(req->params[0]);
    bool rs = db_ticket_order(ticket_id);
    if (rs) {
        status = SUCCESS;
    } else {
        status = FAILED;
    }
    send_response(status, 0, NULL);

}

static void handle_query(request * req)
{
    char ** dbr = 0;
    int row, column;
    char buf[4096];
    char * p = buf;
    int i;
    db_query_ticket(&dbr, &row, &column, req->params[0], req->params[1]);  
    for (i = column; i < (row + 1) * column; i++) {
        sprintf(p, "%s ", dbr[i]); 
        p += strlen(dbr[i]) + 1;
    }
    int status = FAILED;
    if (row>0)
        status = SUCCESS;
    send_response(status, strlen(buf) + 1, buf);
    release_dbr(dbr);
}

static void handle_exit(request * req)
{
    fprintf(stderr, "DISCONNECT\n");
    close_db();
}

static void handle_list_all_tickets(request * req)
{
    char ** dbr = 0;
    int row, column;
    char buf[4096];
    char * p = buf;
    int i;
    db_list_all_tickets(&dbr, &row, &column);  
    for (i = column; i < (row + 1) * column; i++) {
        sprintf(p, "%s ", dbr[i]); 
        p += strlen(dbr[i]) + 1;
    }
    int status = FAILED;
    if (row>0)
        status = SUCCESS;
    send_response(status, strlen(buf) + 1, buf);
    release_dbr(dbr);
}

static void handle_query_orders(request * req)
{
     char ** dbr = 0;
    int row, column;
    char buf[4096];
    char * p = buf;
    int i;
    db_query_orders(&dbr, &row, &column);  
    for (i = column; i < (row + 1) * column; i++) {
        sprintf(p, "%s ", dbr[i]); 
        p += strlen(dbr[i]) + 1;
    }
    int status = FAILED;
    if (row>0)
        status = SUCCESS;
    send_response(status, strlen(buf) + 1, buf);
    release_dbr(dbr);
}
