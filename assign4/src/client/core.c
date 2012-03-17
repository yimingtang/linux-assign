#include "core.h"
#include "defs.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

static void handle_init();
static void handle_register();
static void handle_login();
static void handle_query();
static void handle_exit();
static void handle_order();
static void handle_verified();

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
      case LOGIN:
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

    printf("username: %s\npassword: %s\n",username,passwd);

    // send_request(REGISTER, 2, params);
    // response * resp = get_response();
    // if (resp->status == SUCCESS) {
    //     status = S_VERIFIED;
    // } else {
    //     fputs("VERIFIED ERROR", stdout);
    //     status = S_INIT;
    // }
    status = S_INIT;
}

static void handle_login()
{
    char username[32];
    char passwd[32];
    fputs("\n================== LOG IN =======================\n\n", stdout);
    fputs("Please enter your username and password.\n", stdout);
    get_str("username: ", username);
    get_str("password: ", passwd);
    status = S_VERIFIED;
}
static void handle_query()
{
    fputs("\n================== QUERY ========================\n\n", stdout);
    error_exit(1, "query",NULL);
}
static void handle_exit()
{
    fputs("\n================== EXIT ==========================\n\n", stdout);
    error_exit(1, "exit",NULL);
}
static void handle_order()
{
    fputs("\n================== ORDER =========================\n\n", stdout);
    error_exit(1, "ORDER",NULL);
}
static void handle_verified()
{
    fputs("\n================== VERIFIED ======================\n\n", stdout);
    fputs("Welcome Back! Now, you can do the following things: \n", stdout);
    fputs("    1. QUERT\n", stdout);
    fputs("    2. ORDER\n", stdout);
    fputs("    3. EXIT\n", stdout);
    char c = get_choice();
    switch(c){
         case '1':
            status = S_QUERY;
            break;
         case '2':
            status = S_ORDER;
            break;
        case '3':
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