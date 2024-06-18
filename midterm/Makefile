CC = gcc
CFLAGS = -Wall -pthread
TARGET = http_server

all: $(TARGET)

http_server: http_server.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o
