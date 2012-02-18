#include "defs.h"
const char *USAGE = "This is usage\n";
int maxdepth;
int mindepth;
int curdepth;
struct predicate *pred_list;
struct predicate *last_pred;

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

int main(int argc, const char *argv[])
{
    char *pred_name;
    PFUNC parse_func;
    pred_list = NULL;
    last_pred = NULL;

	if (argc<2) 
		error_exit(1,USAGE);

	int i;
	/*Find where in argv the predicates begin*/
	for (i = 0; i < argc && ('-' != argv[i][0]); i++) {
		;/* do nothing */
        printf("%d \n",i);
	}
	

	maxdepth=mindepth=-1;

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

	return 0;
}
