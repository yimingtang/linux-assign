#ifndef DATABASE_H
#define DATABASE_H
#include "common.h"

/*
 * connect to database
 */
bool connect_db();

/*
 * close the connection with database
 */
void close_db();

/*
 * realse the dbr
 */
void release_dbr(char **dbr);

/*
 * if the user exits
 */
bool has_user(char * username, char * password);

/*
 * register
 */
bool db_register(char * username, char * password);

/*
 * query tickets by from station and to station
 */
bool db_query_ticket(char *** dbr, int * row, int * column, char * from_station, char * to_station);

/*
 * order a ticket
 */
bool db_ticket_order(int id);

/*
 * list all tickets
 */
bool db_list_all_tickets(char *** dbr, int * nrow, int * ncolumn);

/*
 * list all tickets the user has ordered
 */
bool db_query_orders(char *** dbr, int * nrow, int * ncolumn);

#endif
