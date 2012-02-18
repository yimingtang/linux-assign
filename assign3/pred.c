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
    unsigned long type = pred_ptr->args.type;
    return type == entry->d_type;
}
boolean pred_size (struct predicate *pred_ptr,struct dirent *entry)
{
}
boolean pred_atime (struct predicate *pred_ptr,struct dirent *entry)
{
    /*int days_ago = pred_ptr->args.time;*/
    /*struct stat stat_buf;*/
    /*lstat(entry->d_name, &stat_buf);*/
    /*time_t time = stat_buf.st_atime;*/
    /*time_t now = time( NULL );*/
    /*int day_pass = (10000000 - time)/3600/24;*/
    /*return day_pass >= days_ago;*/

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
    unsigned long perm = pred_ptr->args.perm;
    int a = perm %10;
    int c = perm /10;
    int b =c %10;
    c = c /10;
    perm = a + b*8 +c *64;
    struct stat stat_buf;
    lstat(entry->d_name, &stat_buf);
    return perm == (stat_buf.st_mode &07777); 
}

boolean pred_uid (struct predicate *pred_ptr,struct dirent *entry)
{
    uid_t uid = pred_ptr->args.uid;
    struct stat stat_buf;
    lstat(entry->d_name, &stat_buf);
    return uid == stat_buf.st_uid;

}

boolean pred_gid (struct predicate *pred_ptr,struct dirent *entry)
{
    gid_t gid = pred_ptr->args.gid;
    struct stat stat_buf;
    lstat(entry->d_name, &stat_buf);
    return gid == stat_buf.st_gid;

}
