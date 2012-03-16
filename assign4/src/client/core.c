#include "core.h"
#include "defs.h"

static bool handle_register();
static bool handle_login();
static bool handle_query();
static bool handle_exit();
static bool handle_book();


typedef struct _handler_assoc {
    HANDLE_FUNC handle_func;
    char *handler_name;
} handler_assoc;

static handler_assoc const handler_table[]=
{
    {handle_register,"register"},
    {handle_login,"login"},
    {handle_query,"query"},
    {handle_order,"book"},
    {handle_disconnect,"exit"},
    {0,0}
};

HANDLE_FUNC find_handler(char *search_name)
{
    int i;
    if(*search_name == '-')
        search_name++;
    for (i = 0; handler_table[i].handler_name !=0; i++) {
        if (strcmp(handler_table[i].handler_name, search_name) == 0) {
            return handler_table[i].handle_func;
        }
        return NULL;
    }
}

static bool handle_register()
{
    char username[20];
    char passwd[20];
    char passwd_again[20];
    int try = 3;


}
static bool handle_login()
{
}
static bool handle_query()
{
}
static bool handle_exit()
{
}
static bool handle_book()
{
}
