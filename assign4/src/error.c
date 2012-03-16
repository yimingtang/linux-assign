#include "error.h"
#include <stdio.h>

static void print_msg(const char *msg, char *extra);

void error_exit(int exit_code, const char * msg, char *extra)
{
    print_msg(msg, extra);
    exit(exit_code);
}

void error_msg(const char *msg, char *extra)
{
   print_msg(msg, extra); 
}

static void print_msg(const char *msg, char *extra)
{
    fprintf(stderr, "Oops, we encountered an error:");
    if (extra == NULL) 
        fprintf(stderr, msg);
    else 
        fprintf(stderr, msg, extra);     
    fputc('\n',stderr);
}

