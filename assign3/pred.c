#include <defs.h>
#include <fnmatch.h>
/* Here we use table driven programming
 * predicate & string pair
 */
struct pred_assoc
{
    PFUNC pred_func;
    char *pred_name;
};


struct pred_assoc pred_table[]=
{
    {pred_name,"name  "},
    {pred_type,"type  "},
    {pred_size,"size  "},
    {pred_atime,"atime "},
    {pred_ctime,"ctime "},
    {pred_mtime,"mtime "},
    {pred_regex,"regex "},
    {pred_perm,"perm  "},
    {pred_uid,"uid   "},
    {pred_gid,"gid   "},
    {0,"none   "},
};


struct op_assoc
{
    short type;
    char *type_name;
};



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

