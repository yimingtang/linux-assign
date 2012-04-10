#ifndef ERROR_H
#define ERROR_H

/*
 * error and exit, if need extra messages give a value, 
 * otherwise a NULL should be passed
 */
void error_exit(int exit_code,const char *msg, char *extra);

/*
 * error message
 */
void error_msg(const char *msg, char *extra);

#endif
