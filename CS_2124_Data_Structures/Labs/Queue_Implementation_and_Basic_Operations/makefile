lab4.exe:main.o queue.o
	gcc -o lab4.exe main.o queue.o

main.o:main.c queue.h
	gcc -c -o main.o main.c


queue.o:queue.c queue.h
	gcc -c -o queue.o queue.c

clean:
	rm *.o *.exe
