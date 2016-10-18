OBJS = main.o sub.o
CFLAGS = -O -g -Wall
TARGET = hello

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean: 
	rm -f *.o
