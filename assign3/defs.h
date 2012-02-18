#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fnmatch.h>
#include <dirent.h>
#include <pwd.h>
#include <limits.h>

typedef	int  boolean;
#define true    1
#define false   0

/*
 * Pointer to function returning boolean
 */
typedef boolean (*PFUNC)();

enum comparison_type
{
    COMP_GT,
    COMP_LT,
    COMP_EQ
};

struct time_val
{
    enum comparison_type kind;
    unsigned long value;
};

struct size_val
{
    enum comparison_type kind;
    int blocksize;
    unsigned long size;
};

struct	predicate
{
    PFUNC pred_func;
    struct predicate *pred_next;
    union
    {
        char *str;  //fstype lname,name,path
        struct time_val time;   // atime ctime mtime
        struct size_val size;   // size
        uid_t uid;  //user
        gid_t gid;  //group
        unsigned long perm; //perm
        unsigned long type; //type
        FILE *stream;   //fprint...
    }args;
};

/*pred.c*/
boolean pred_name (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_type (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_size (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_atime (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_ctime (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_mtime (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_regex (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_perm (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_uid (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);
boolean pred_gid (char *pathname, struct stat *stat_buf, struct predicate *pred_ptr);

/*parser.c*/
PFUNC find_parser (char *search_name);
boolean parse_print (char *argv[], int arg_ptr);



extern struct predicate *pred_list;
extern struct predicate *last_pred;
extern int maxdepth;
extern int mindepth;
extern int curdepth;

