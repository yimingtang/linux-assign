#ifndef DATABASE_H
#define DATABASE_H
#include "common.h"

bool connect_db();
void close_db();
void release_dbr(char **dbr);
bool has_user(char * username, char * password);
bool db_register(char * username, char * password);
bool db_query_ticket(char *** dbr, int * row, int * column, char * from_station, char * to_station);
bool db_ticket_order(int id);
#endif