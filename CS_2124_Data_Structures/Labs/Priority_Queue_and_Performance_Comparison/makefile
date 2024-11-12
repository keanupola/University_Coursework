lab6.exe: main.o priority_queue.o heap.o
	gcc -o lab6.exe main.o priority_queue.o heap.o

main.o: main.c priority_queue.h heap.h
	gcc -c -o main.o main.c

priority_queue.o: priority_queue.c priority_queue.h
	gcc -c -o priority_queue.o priority_queue.c

heap.o: heap.c heap.h
	gcc -c -o heap.o heap.c

clean:
	rm *.o *.exe
