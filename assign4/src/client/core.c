#include <stdio.h>
#include <string.h>
#include "core.h"
#include "defs.h"
#include "error.h"
#include "connection.h"

static void handle_init();
static void handle_register();
static void handle_login();
static void handle_query();
static void handle_exit();
static void handle_order();
static void handle_verified();
static void handle_query_orders();

static char get_choice();
static void get_str(char * prompts, char * result);
static void read_flush();

C_Status status;

void start_client() {
  status = S_INIT;
  while (true) {
    switch(status) {
      case S_INIT:
        handle_init(); 
        break;
      case S_EXIT:
        handle_exit();
        return;
      case S_LOGIN:
        handle_login();
        break;
      case S_REGISTER:
        handle_register();
        break;
      case S_VERIFIED:
        handle_verified();
        break;
      case S_ORDER:
        handle_order();
        break;
      case S_QUERY_ORDER:
        handle_query_orders();
        break;
      case S_QUERY:
        handle_query();
      default:
        break;
    }
  }
}

static void handle_init()
{
    fputs("\n================== START ==========================\n\n", stdout);
    fputs("Welcome to the Railway Ticket System, YOU CAN CHOOSE THE FOLLOWING OPTIONS:\n", stdout);
    fputs("    1. LOG IN\n", stdout);
    fputs("    2. REGISTER\n", stdout);
    fputs("    3. EXIT\n", stdout);
    char c = get_choice();
    switch(c){
         case '1':
            status = S_LOGIN;
            break;
         case '2':
            status = S_REGISTER;
            break;
        case '3':
            status = S_EXIT;
            break;
    }
}

static void handle_register()
{
    char username[32];
    char passwd[32];
    char passwd_again[32];
    int try = 3;
    fputs("\n================== REGISTER ==========================\n\n", stdout);
    while(try > 0){
        fputs("Please enter your username and password. \n", stdout);
        get_str("username: ", username);
        get_str("password: ", passwd);
        get_str("password again: ", passwd_again);
        if (strcmp(passwd,passwd_again) == 0)
            break;
        else{
            try--;
            fputs("Opps, not the same password.\n", stdout);
        }
    }

    if(try == 0){
        fputs("redirect to init\n", stdout);
        status = S_INIT;
        return;
    }

    char * params[2];
    params[0] = username;
    params[1] = passwd;

    send_request(REGISTER, 2, params);
    response * rs = recv_response();
    if (rs->status == SUCCESS) {
        status = S_LOGIN;
    } else {
        fputs("Can't register. perhaps: already exists", stdout);
        status = S_INIT;
    }
}

static void handle_login()
{
    char username[32];
    char passwd[32];
    fputs("\n================== LOG IN =======================\n\n", stdout);
    fputs("Please enter your username and password.\n", stdout);
    get_str("username: ", username);
    get_str("password: ", passwd);
    char * params[2];
    params[0] = username;
    params[1] = passwd;

    send_request(LOGIN, 2, params);
    response * rs = recv_response();
    if (rs->status == SUCCESS) {
        status = S_VERIFIED;
    } else {
        fputs("Can't LOGIN. perhaps: username or password wrong", stdout);
        status = S_INIT;
    }
}
static void handle_query()
{
    char from_station[32];
    char to_station[32];
    fputs("\n================== QUERY ========================\n\n", stdout);
    send_request(LIST_ALL, 0, NULL);
    response * rs1 = recv_response();
    if (rs1->status == SUCCESS) {    
        char *data = strtok(rs1->result, " "); 
        fprintf(stdout, "\tfrom\t\tto\n");
        int count =1;
        while(data != NULL) {
            fprintf(stdout, "\t%s", data);
            if(count %2 ==0)
                fputc('\n',stdout);
            count ++;
            data = strtok(NULL, " ");
        }
        fputc('\n',stdout);
    }else{
        error_msg("query error",NULL);
    }

    fputs("\n********* ONLY THE STATIONS LISTED IS AVAILABLE**********\n\n", stdout);
    get_str("from: ", from_station);
    get_str("to: ", to_station);

    char * params[2];
    params[0] = from_station;
    params[1] = to_station;

    send_request(QUERY, 2, params);
    response * rs2 = recv_response();
    if (rs2->status == SUCCESS) {
        char *data = strtok(rs2->result, " "); 
        fprintf(stdout, "\n\tid\tform\t\tto\t\tprice\tdays_left\n");
        while(data != NULL) {
            fprintf(stdout, "\t%s", data);
            data = strtok(NULL, " ");
        }
        fputc('\n',stdout);
    }else{
        error_msg("query error",NULL);
    }

    status = S_VERIFIED;
}


static void handle_query_orders()
{
    fputs("\n================== QUERY  ORDERS====================\n\n", stdout);
    send_request(QUERY_ORDER, 0, NULL);
    response * rs = recv_response();
    if (rs->status == SUCCESS) {
        char *data = strtok(rs->result, " "); 
        fprintf(stdout, "\tid\tfrom\t\tto\t\tprice\tusername\n");
        int count = 1;
        while(data != NULL) {
            fprintf(stdout, "\t%s", data);
            if(count % 5 == 0)
                fputc('\n',stdout);
            count ++;
            data = strtok(NULL, " ");
        }
        fputc('\n',stdout);
    }else{
        error_msg("query error",NULL);
    }
    status = S_VERIFIED;
}

static void handle_exit()
{
    fputs("\n================== EXIT ==========================\n\n", stdout);
    send_request(DISCONNECT, 0, NULL);
}
static void handle_order()
{
    fputs("\n================== ORDER =========================\n\n", stdout);
    char ticket_id[8];
    get_str("ticket_id: ", ticket_id);

    char * params[1];
    params[0] = ticket_id;

    send_request(ORDER, 1, params);
    response * rs = recv_response();
    if (rs->status == SUCCESS) {
        fputs("\n#############  ORDER SUCCESS ##############\n", stdout);
    } else {
        error_msg("order error",NULL);
    }
    status = S_VERIFIED;
}
static void handle_verified()
{
    fputs("\n================== VERIFIED ======================\n\n", stdout);
    fputs("Welcome Back! Now, you can do the following things: \n", stdout);
    fputs("    1. QUERY TICKETS\n", stdout);
    fputs("    2. ORDER\n", stdout);
    fputs("    3. QUERY YOUR ORDER\n", stdout);
    fputs("    4. EXIT\n", stdout);
    char c = get_choice();
    switch(c){
         case '1':
            status = S_QUERY;
            break;
         case '2':
            status = S_ORDER;
            break;
        case '3':
            status = S_QUERY_ORDER;
            break;
        case '4':
            status = S_EXIT;
            break;
    }
}

static char get_choice() 
{
    fputs("Please Enter YOU CHOICE : ", stdout);
    char c = getchar();
    read_flush();
    return c;
}

static void get_str(char *prompts, char *result) 
{
    fputs(prompts, stdout);
    fscanf(stdin, "%s", result);
    read_flush();
}

// ignore any buffer in stdin
static void read_flush()
{
    char c;
    while((c = getchar()) != '\n')
        ;
}
