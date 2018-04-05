//*************************************************************
// Author: Tyler Matthews, Matthew Monnik
// Date: 04/03/2018
// Reader writer v2, writer preference 
//
//
//*************************************************************


#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define NO_WRITERS	5
#define NO_READERS	100

int writecount = 0;
sem_t sem1, rsem;

//writer
void *writer(void *param) 
{
	int thread = (intptr_t)param;
	srand(time(NULL));

	while (1) 
	{

		//sleep before reading
		usleep(thread * 30000);

		/// decrement writecount sem, update write count
		sem_wait(&sem1);
		writecount++;

		// if its the first writer lock the read sempahore.
		if (writecount == 1) sem_wait(&rsem);

		// release write sem
		sem_post(&sem1);

		// display status's
		printf("Writer %d is writing.\n", thread);
		usleep(thread * 15000);
		printf("Writer %d done writing.\n", thread);

		// decrement writer count sem, update writer count
		sem_wait(&sem1);
		writecount--;

		// If last writers and no readers, release reader sem
		if (writecount == 0) sem_post(&rsem);

		//release writer sem
		sem_post(&sem1);
	}

	return NULL;

}

//reader
void *reader(void *param) 
{

	int thread = (intptr_t)param;
	srand(time(NULL));

	while (1) 
	{
		
		// sleep before reading again
		usleep(thread * 30000);

		// get reader
		sem_wait(&rsem);

	    //display status's
		printf("Reader %d is reader.\n", thread);
		usleep(thread * 10000);
		printf("Reader %d done reading.\n", thread);

		// release reader sem
		sem_post(&rsem);
	}
	return NULL;
}

int main (int argc, char *argv[]) 
{

	printf("readwrite began with %d writers and %d readers.\n", NO_WRITERS,
			NO_READERS);

	// create writers and readers
	pthread_t *threads = malloc((NO_WRITERS + NO_READERS) * sizeof(pthread_t));

	pthread_t tid;
	pthread_attr_t attr;

	
	sem_init(&sem1, 0, 1);
	sem_init(&rsem, 0, 1);

	
	pthread_attr_init(&attr);

	int i = 0;

	// creater writer threads
	while (i < NO_WRITERS) 
	{	
		pthread_create(threads + i, &attr, writer, (void *)(intptr_t)i + 1);
		i++;
	}

	i = 0;
	
	//create reader threads
	while (i < NO_READERS) 
	{	
		pthread_create(threads + i + NO_WRITERS, &attr, reader, (void *)(intptr_t)i + 1);
		i++;
	}

	i = 0;

	// wait on threads
	while (i < (NO_READERS + NO_WRITERS)) 
	{
		pthread_join(*(threads + i), NULL);
		i++;
	}
	return  0;

}
