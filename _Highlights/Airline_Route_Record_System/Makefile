CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRCS = main.c route-records.c
OBJS = $(SRCS:.c=.o)

TARGET = project2

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c route-records.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /F /Q *.o project2.exe

