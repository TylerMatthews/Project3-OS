make: memsim.o
	gcc readwrite3.o -o readwrite

memsim.o: readwrite3.c
	gcc -c readwrite3.c

clean:
	rm *.o readwrite3