CC = gcc
CFLAGS = -Wall -g
DEPS = assignment2pt1.h
OBJ = main.o assignment2pt1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

p_check: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o p_check
