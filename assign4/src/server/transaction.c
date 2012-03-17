#include "transaction.h"
#include "defs.h"
#include "connection.h"
#include "common.h"



static void handle_login(request * req);
static void handle_register(request * req);
static void handle_order(request * req);
static void handle_query(request * req);
static void handle_exit(request * req);

int start_service() {
  //connect_db();
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
        fprintf(stderr, "QUIT\n");
       // state = IDLE;
       // close_db();
        return 0;
      case QUERY:
        handle_query(req);
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
}
static void handle_register(request * req)
{
    //bool rs = register_user(request->params[0], request->params[1]);
    //response_status status;
    fprintf(stderr, "%s %s\n", req->params[0],req->params[1] );
    send_response(SUCCESS, 0, NULL);

}
static void handle_order(request * req)
{

}
static void handle_query(request * req)
{

}
static void handle_exit(request * req)
{

}