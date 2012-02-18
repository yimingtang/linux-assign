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

/*pred.c*/
boolean pred_name (struct predicate *pred_ptr,struct dirent *entry)
{
    char *name = pred_ptr->args.str;
    return fnmatch(name,entry->d_name,0)==0;

}
boolean pred_type (struct predicate *pred_ptr,struct dirent *entry)
{

}
boolean pred_size (struct predicate *pred_ptr,struct dirent *entry)
{
}
boolean pred_atime (struct predicate *pred_ptr,struct dirent *entry)
{

}
boolean pred_ctime (struct predicate *pred_ptr,struct dirent *entry)
{
}
boolean pred_mtime (struct predicate *pred_ptr,struct dirent *entry)
{

}
boolean pred_regex (struct predicate *pred_ptr,struct dirent *entry)
{

}
boolean pred_perm (struct predicate *pred_ptr,struct dirent *entry)
{

}
boolean pred_uid (struct predicate *pred_ptr,struct dirent *entry)
{

}
