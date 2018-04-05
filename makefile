make: project3_matthewsmonnik.o
	gcc -pthread project3_matthewsmonnik.o -o project3_matthewsmonnik

project3_matthewsmonnik.o: project3_matthewsmonnik.c
	gcc -c project3_matthewsmonnik.c

clean:
	rm *.o project3_matthewsmonnik
