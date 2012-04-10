#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "database.h"

static sqlite3 * db;
int user_id;

bool connect_db() 
{
    int rc;  
    rc = sqlite3_open("../db/tickets.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return false;
    }
    fprintf(stderr, "database conneted!\n");
    return true;
}

void close_db()
{
    sqlite3_close(db);
}

void release_dbr(char ** dbr)
{
    sqlite3_free_table(dbr); 
}

bool has_user(char * username, char * password)
{
    char sql[128];
    int nrow, ncolumn;
    char ** dbr;
    char * errmsg;
    bool result = false;
    sprintf(sql, "select id from user where username=\"%s\" and passwd=\"%s\"", username, password); 
    sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
    fprintf(stderr, "%d\n%s|\n%s|\n",nrow,username,password);
    if (nrow > 0) {
        user_id = atoi(dbr[1]);
        result = true;
    }
    sqlite3_free_table(dbr);
    return result;
}

bool db_register(char * username, char * password)
{
    char sql[128];
    int nrow, ncolumn;
    char ** dbr;
    char * errmsg;
    sprintf(sql, "select * from user where username=\"%s\"", username); 
    sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
    sqlite3_free_table(dbr);
    if (nrow > 0)
        return false;
    sprintf(sql, "insert into user(\"username\", \"passwd\") values(\"%s\", \"%s\")", username, password);
    sqlite3_exec(db, sql, NULL, NULL, &errmsg); 
    return true;
}

bool db_query_ticket(char *** dbr, int * row, int * column, char * from_station, char * to_station) 
{
    char sql[256];
    char * errmsg;
    sprintf(sql, "select * from ticket where from_station = '%s' and to_station = '%s'", from_station, to_station);
    sqlite3_get_table(db, sql, dbr, row, column, &errmsg);   
    return true;
} 

bool db_ticket_order(int id)
{
    char sql[128];
    int nrow, ncolumn;
    char ** dbr;
    char * errmsg;

    sprintf(sql, "select * from ticket where  id = %d ", id);
    sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
    
    if (nrow == 0) {
      sqlite3_free_table(dbr); 
      return false;
    }
      
  //  train_id = atoi(dbr[2]);
   // num = atoi(dbr[3]);
   // sqlite3_free_table(dbr); 
    
    // sprintf(sql, "select count(*) from sell_log where train_id = %d and buy_date = '%s'", train_id, date);
    // sqlite3_get_table(db, sql, &dbr, &nrow, &ncolumn, &errmsg);
    // if (num <= atoi(dbr[1])) {
    //   sqlite3_free_table(dbr); 
    //   return false;
    // }
    // sqlite3_free_table(dbr); 
    
    sprintf(sql, "insert into ticket_order(\"user_id\", \"ticket_id\", \"date\") values(%d, %d, datetime('now', 'localtime'))", 
              user_id, id);
    sqlite3_exec(db, sql, NULL, NULL, &errmsg); 
    return true;
}

bool db_query_orders(char *** dbr, int * nrow, int * ncolumn)
{
    char sql[512];
    char * errmsg;
    sprintf(sql, "select ticket_order.id, ticket.from_station, ticket.to_station, ticket.price, user.username from user, ticket, ticket_order where ticket.id = ticket_order.ticket_id and user.id = ticket_order.user_id and user.id = %d;", user_id);
    sqlite3_get_table(db, sql, dbr, nrow, ncolumn, &errmsg);
    return true;
}

bool db_list_all_tickets(char *** dbr, int * nrow, int * ncolumn)
{
    char sql[128];
    char * errmsg;
    sprintf(sql, "select from_station, to_station from ticket");
    sqlite3_get_table(db, sql, dbr, nrow, ncolumn, &errmsg);
    return true;
}


