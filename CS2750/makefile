CC = gcc
CFLAGS = -W -WALL
TARGET1 = master
TARGET2 = worker

OBJS1 = master.o
OBJS2 = worker.o

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	$(CC) -o $(TARGET1) $(OBJS1)

$(TARGET2): $(OBJS2)
	$(CC) -o $(TARGET2) $(OBJS2)

master.o: master.c
	$(CC) -c master.c

worker.o: worker.c
	$(CC) -c worker.c
clean:
	/bin/rm -f *.o $(TARGET1) $(TARGET2)
