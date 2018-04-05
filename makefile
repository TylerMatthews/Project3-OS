make: readwrite3.o
	gcc -pthread readwrite3.o -o readwrite3

readwrite3.o: readwrite3.c
	gcc -c readwrite3.c

clean:
	rm *.o readwrite3
