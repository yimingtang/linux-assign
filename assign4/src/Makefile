CC = gcc
CFLAGS = -Wall -c -I ./

SERV_DIR=server
CLIENT_DIR=client
SERV_TARGET=server.out
CLIENT_TARGET=client.out

CLIENT_OBJS = error.o  $(CLIENT_DIR)/client.o  $(CLIENT_DIR)/core.o  socket.o connection.o
SERVER_OBJS = error.o  $(SERV_DIR)/server.o socket.o connection.o $(SERV_DIR)/transaction.o $(SERV_DIR)/database.o 

all: clean server.out client.out
	
client.out: $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT_TARGET)
server.out: $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERV_TARGET) -L /usr/lib/libsqlite3.so -lsqlite3
client.o: $(CLIENT_DIR)/client.c
	$(CC) $(CFLAGS) $< -o client.o
core.o: $(CLIENT_DIR)/core.c
	$(CC) $(CFLAGS) $< -o core.o
error.o: error.c
	$(CC) $(CFLAGS) $< -o error.o
fifo.o: socket.c
	$(CC) $(CFLAGS) $< -o socket.o
server.o:$(SERV_DIR)/server.c
	$(CC) $(CFLAGS) $< -o server.o
connection.o:connection.c
	$(CC) $(CFLAGS) $< -o connection.o
trasaction.o: $(SERV_DIR)/transaction.c
	$(CC) $(CFLAGS) $< -o transaction.o
database.o:$(SERV_DIR)/database.c
	$(CC) $(CFLAGS) $< -o database.o 


clean:
	rm -f *.o
	rm -f $(SERV_DIR)/*.o
	rm -f $(CLIENT_DIR)/*.o
	rm -f server.out
	rm -f client.out
