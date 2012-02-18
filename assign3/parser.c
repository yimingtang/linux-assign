#include "defs.h"

static boolean parse_name(char *argv[],int *arg_ptr);
static boolean parse_size(char *argv[],int *arg_ptr);
static boolean parse_type(char *argv[],int *arg_ptr);
static boolean parse_atime(char *argv[],int *arg_ptr);
static boolean parse_ctime(char *argv[],int *arg_ptr);
static boolean parse_mtime(char *argv[],int *arg_ptr);
static boolean parse_uid(char *argv[],int *arg_ptr);
static boolean parse_gid(char *argv[],int *arg_ptr);
static boolean parse_perm(char *argv[],int *arg_ptr);
static boolean parse_regex(char *argv[],int *arg_ptr);
static boolean parse_help(char *argv[],int *arg_ptr);
static boolean parse_version(char *argv[],int *arg_ptr);
static boolean parse_maxdepth(char *argv[],int *arg_ptr);
static boolean parse_mindepth(char *argv[],int *arg_ptr);

struct parser_assoc
{
    PFUNC parser_func;
    char *parser_name;
};


static struct parser_assoc const parser_table[]=
{   
    {parse_name,"name"},
    {parse_type,"type"},
    {parse_size,"size"},
    {parse_atime,"atime"},
    {parse_ctime,"ctime"},
    {parse_mtime,"mtime"},
    {parse_uid,"uid"},
    {parse_gid,"gid"},
    {parse_regex,"regex"},
    {parse_perm,"perm"},
    {parse_help,"help"},
    {parse_version,"version"},
    {parse_maxdepth,"maxdepth"},
    {parse_mindepth,"mindepth"},
    {0,0}
};
   
PFUNC find_parser(char *search_name)
{
    int i;
    if(*search_name == '-')
        search_name++;
    for (i = 0; parser_table[i].parser_name!=0; i++) {
        if (strcmp(parser_table[i].parser_name,search_name) == 0) {
            return parser_table[i].parser_func;
        }
    }
    return NULL;
}


static boolean parse_name(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_name);
    pred->args.str = argv[*arg_ptr];
    (*arg_ptr)++;
    return true;
}
static boolean parse_size(char **argv,int *arg_ptr)
{

}
static boolean parse_type(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_type);
    unsigned long type;
    switch(argv[*arg_ptr][0]) {
        case 'b': type = DT_BLK; break;
        case 'c': type = DT_CHR; break;
        case 'd': type = DT_DIR; break;
        case 'p': type = DT_FIFO; break;
        case 'f': type = DT_REG; break;
        case 'l': type = DT_LNK; break;
        case 's': type = DT_SOCK; break;
        default: error_exit(1, "unrecognized file type.");
    }

    pred->args.type = type;
    (*arg_ptr)++;
    return true;

}
static boolean parse_atime(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_atime);
    pred->args.time = atoi(argv[*arg_ptr]);
    (*arg_ptr)++;
    return true;

}
static boolean parse_ctime(char **argv,int *arg_ptr)
{

}
static boolean parse_mtime(char **argv,int *arg_ptr)
{
}
static boolean parse_uid(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_uid);
    pred->args.uid = atoi(argv[*arg_ptr]);
    (*arg_ptr)++;
    return true;

}
static boolean parse_gid(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_gid);
    pred->args.gid = atoi(argv[*arg_ptr]);
    (*arg_ptr)++;
    return true;

}
static boolean parse_perm(char **argv,int *arg_ptr)
{
    struct predicate *pred;
    if ((argv == NULL)||(argv[*arg_ptr] == NULL)) 
        return false;
    pred = insert_pred(pred_perm);
    pred->args.perm = atoi(argv[*arg_ptr]);
    (*arg_ptr)++;
    return true;

}

static boolean parse_regex(char **argv,int *arg_ptr)
{

}
static boolean parse_help(char **argv,int *arg_ptr)
{

}
static boolean parse_version(char **argv,int *arg_ptr)
{

}
static boolean parse_maxdepth(char **argv,int *arg_ptr)
{

}
static boolean parse_mindepth(char **argv,int *arg_ptr)
{
}
