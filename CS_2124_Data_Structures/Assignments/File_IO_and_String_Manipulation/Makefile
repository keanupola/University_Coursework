CC = gcc

TARGETS = C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
