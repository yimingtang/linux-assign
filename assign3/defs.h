#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef	int boolean;
#define		true	1
#define		false	0

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

/*
 *Two kinds:  1. real predicate
 *            2. operators for combining predicate
 */
enum predicate_type
{
    NO_TYPE,
    PRIMARY_TYPE,
    UNI_OP,
    BI_OP,
    LEFT_PAREN,
    RIGHT_PAREN
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
    char *p_name; //only used in debug mode
    PFUNC pred_func;
    struct predicate *pred_next;
    struct predicate *pred_left;
    struct predicate *pred_right;
    enum predicate_type p_type;

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

/*
 *parser.c
 */

PFUNC find_parser (char *search_name);
boolean parse_close (char *argv[], int *arg_ptr);
boolean parse_open (char *argv[], int arg_ptr);
boolean parse_print (char *argv[], int arg_ptr);


/*
 *pred.c
 */
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

char *find_pred_name (PFUNC pred_func);

