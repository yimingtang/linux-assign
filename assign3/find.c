#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

const char *USAGE = "This is usage";
int maxdepth;
int mindepth;
int curdepth;

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
	exit(exit_code);	
}

int main(int argc, const char *argv[])
{
	if (argc<2) 
		error_exit(1,USAGE);

	int i;
	/*Find where in argv the predicates begin*/
	for (i = 0; i < argc && strchr("!-(),", argv[i][0] == NULL); i++) {
		;/* do nothing */
	}
	
	maxdepth=mindepth=-1;
	
	


	return 0;
}
