#include "defs.h"

struct predicate *get_new_pred()
{

    struct predicate *new_pred; 
    if(pred_list == NULL){
        pred_list = (struct predicate *)malloc (sizeof(struct predicate));
        last_pred =pred_list;
    }else{
        new_pred = (struct predicate *)malloc (sizeof(struct predicate));
        last_pred->pred_next=new_pred;
        last_pred = new_pred;
    } 

    last_pred->pred_func = NULL;
    last_pred->pred_next = NULL;
    last_pred->args.str = NULL;
    return last_pred;
}

struct predicate * insert_pred(boolean (*pred_func)(/* ??? */))
{
    struct predicate * p;
    p = get_new_pred();
    p->pred_func = pred_func;
    p->args.str = NULL;
    return p; 
}

boolean pred_name(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_atime(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{


}

boolean pred_ctime(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_mtime(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_size(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_type(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_perm(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_regex(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_uid(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

boolean pred_gid(char *pathname,struct stat *stat_buf, struct predicate *pred_ptr)
{

}

