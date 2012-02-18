#include "defs.h"
const char *USAGE = "This is usage\n";
int maxdepth;
int mindepth;
int curdepth;
struct predicate *pred_list;
struct predicate *last_pred;
struct dir *dir_list;
struct dir *last_dir;

struct dir *get_new_dir()
{
    struct dir *new_dir;
    if(dir_list == NULL){
        dir_list = (struct dir *) malloc(sizeof(struct dir));
        last_dir = dir_list;
    }else{

        new_dir = (struct dir *) malloc(sizeof(struct dir));
        last_dir->next_dir = new_dir;
        last_dir = new_dir;
    }
    last_dir->dir_name = NULL;
    last_dir->next_dir = NULL;
    return last_dir; 
}

char *_name(char *dir_name)
{
    size_t len = strlen(dir_name);
    char *dir = malloc(len + 1);
    if(dir) {
        strcpy(dir, dir_name);
        if('/' == dir[len-1])
            dir[len-1] = '\0';
    }

    return dir;
}

struct dir * insert_dir(char *dir_name)
{
    struct dir *d;
    d=get_new_dir();
    d->dir_name = _name(dir_name);
    return d;

}

void free_dir_list()
{
    struct dir *next;
    while(dir_list != NULL){
        next = dir_list->next_dir;
        free(dir_list->dir_name);
        free(dir_list);
        dir_list=next;
    }
}



/*
 * Print error messages to stderr
 */
void error_exit(int exit_code, const char *msg)
{
	fprintf(stderr,"error: ");
	if(msg !=NULL)
		fprintf(stderr,msg);
	else
		fprintf(stderr,"unknown error,exit");
    fputc('\n',stderr);
	exit(exit_code);	
}

void print_dir_list()
{
    struct dir *cur_dir=dir_list;
    while(cur_dir->dir_name != NULL){
        printf("path: %s \n",cur_dir->dir_name);
        if(cur_dir->next_dir != NULL)
            cur_dir=cur_dir->next_dir;
        else 
            break;
    }
}

void print_pred_list()
{
    struct predicate *cur_pred = pred_list;
    while(cur_pred->pred_func!= NULL){
        printf("pred: %s \n",cur_pred->args.str);
        if(cur_pred->pred_next != NULL)
            cur_pred=cur_pred->pred_next;
        else 
            break;
    }    
}

boolean pred_test(struct predicate *pred_list,struct dirent *entry)
{
    struct predicate *cur_pred = pred_list;
    while(cur_pred->pred_func!= NULL){
        if(!(*cur_pred->pred_func)(cur_pred,entry))
            return false;
        if(cur_pred->pred_next != NULL)
            cur_pred=cur_pred->pred_next;
        else 
            break;
    }
    return true;    
}

char *_long_name(const char *parent_dir, const char *dir)
{
    char *long_name = malloc(strlen(parent_dir) + strlen(dir) + 2);

    if(long_name) {
        strcpy(long_name, parent_dir);
        strcat(long_name, "/");
        strcat(long_name, dir);
    }

    return long_name;
}


void _traverse(char *dir,struct predicate *pred, int depth, int mindepth, int maxdepth)
{
    if(depth > maxdepth)
        return;

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "ERROR: cannot open directory.");
        return;
    }

    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        /* ignore . and .. */
        if(strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0)
            continue;

        if(depth >= mindepth && pred_test(pred, entry)) {
            
            printf("%s/%s\n", dir, entry->d_name);
        }

        lstat(entry->d_name, &statbuf);
        /* if entry is directory */
        if(S_ISDIR(statbuf.st_mode)) {
            char *long_name = _long_name(dir, entry->d_name);
            /* Recurse at a new indent level */
            _traverse(long_name, pred, depth+1, mindepth, maxdepth);
            free(long_name);
        }
    }
    chdir("..");
    closedir(dp);
}



void traverse(char *dir,struct predicate *pred, int min_depth, int max_depth)
{

    int depth = 0; 
    if(depth > max_depth)
        return;

    struct stat statbuf;
    if(lstat(dir, &statbuf)) {
        error_exit(1, "cannot stat file");
    }

    struct dirent *entry = (struct dirent *)malloc(sizeof(struct dirent));
    char *dup1 = strdup(dir);
    char *dup2 = strdup(dir);
    char *dir_name = dirname(dup1);
    char *base_name = basename(dup2);
    chdir(dir_name);
    strncpy(entry->d_name, base_name, 256);
    if(S_ISREG(statbuf.st_mode)) {
        entry->d_type = DT_REG;
    } else if(S_ISDIR(statbuf.st_mode)){
        entry->d_type = DT_DIR;
    } else if(S_ISCHR(statbuf.st_mode)){
        entry->d_type = DT_CHR;
    } else if(S_ISBLK(statbuf.st_mode)){
        entry->d_type = DT_BLK;
    } else if(S_ISFIFO(statbuf.st_mode)){
        entry->d_type = DT_FIFO;
    } else if(S_ISLNK(statbuf.st_mode)){
        entry->d_type = DT_LNK;
    } else if(S_ISSOCK(statbuf.st_mode)){
        entry->d_type = DT_SOCK;
    } else {
        entry->d_type = DT_UNKNOWN;
    }

    if(depth >= min_depth && pred_test(pred, entry)) {
        printf("%s/%s\n", dir_name, base_name);
    }

    /* if is directory, traverse it */
    if(DT_DIR == entry->d_type)
        _traverse(dir, pred, depth+1, mindepth, maxdepth);
    printf("operation completed.\n");
    free(dup2);
    free(dup1);
    free(entry);
}

int main(int argc, const char *argv[])
{
    char *pred_name;
    char *dir_name;
    PFUNC parse_func;
    pred_list = NULL;
    last_pred = NULL;
    dir_list = NULL;
    last_dir = NULL;
    struct dir *cur_dir;

    if (argc<2) 
        error_exit(1,USAGE);

    int i;
    /*Find where in argv the predicates begin*/
    for (i = 1; i < argc && ('-' != argv[i][0]); i++) {
        dir_name = argv[i];
        insert_dir(dir_name);
    }
    
    if (i == argc) {
        error_exit(1,"no predicates.");
    }
	
    maxdepth = INT_MAX;
    mindepth = -1;

    /*
     *read predicates then parse
     */
    while(i < argc){
        if ('-' != argv[i][0]) {
            error_exit(1,USAGE);
        }
        pred_name = argv[i];
        parse_func=find_parser(pred_name);
        if(parse_func == NULL)
            error_exit(1,"invalid predicate."); 
        i++;
        if(!(*parse_func)(argv,&i)){
            if(argv[i] == NULL)
                error_exit(1,"missing argument.");
            else
                error_exit(1,"invalid argument.");
        }
    }   
    /* search file    */
#ifdef DEBUG
    if(dir_list != NULL)
        print_dir_list();
    if(pred_list != NULL)
        print_pred_list();
#endif
    if(dir_list == NULL)
        insert_dir(".");
    cur_dir = dir_list;

    while(cur_dir->dir_name != NULL){
        traverse(cur_dir->dir_name,pred_list,mindepth,maxdepth);
        if(cur_dir->next_dir != NULL)
            cur_dir=cur_dir->next_dir;
        else 
            break;
    }
    

    /*free memory*/
    free_dir_list();
    /*free_pred_list();*/

	return 0;
}
