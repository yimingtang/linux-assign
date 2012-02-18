CC = gcc
OBJS = parser.o find.o pred.o
TARGET = myfind
CFLAGS= -Wall

myfind: find.o parser.o pred.o
	$(CC) $(OBJS) -o $(TARGET)
find.o: find.c
	$(CC) $(CFLAGS) -c $<

parser.o: parser.c
	$(CC) $(CFLAGS) -c $<
pred.o: pred.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGET)
