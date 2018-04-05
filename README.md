First compile the makefile.
Then, to run, do ./readwrite3 
IF AFTER COMPILING IT DOES NOT RUN,
Please try recompiling putting -pthread after gcc: i.e gcc -pthread .readwrite3.c
To run with a different number of readers and writers, open the .c file and change the values associated with the following variables #define at the top.

NO_WRITERS - to change the number of writers
NO_READERS - to change the number of reads
