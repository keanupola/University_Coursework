lab5.exe:main.o heap.o
	gcc main.o heap.o -o lab5.exe 

main.o:main.c heap.h
	gcc -c main.c -o main.o

heap.o:heap.c heap.h
	gcc -c heap.c -o heap.o


clean:
	rm *.o *.exe
