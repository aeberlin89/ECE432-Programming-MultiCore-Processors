#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define N 6
#define NEXT(x) ((x + 1) % N)

pthread_t tid[3];
int buffer[N], in=0, out=0, count=0;



void* producer(void *ptr)
{
	srand(time(NULL));
	int item,i;
  while (1) {

	while (count == N)
		; // wait
	item = rand()%10;
	printf("Insert: %d\n",item);
	buffer[in] = item;
	sleep(rand()%5);
	in = NEXT(in);
	count++;
	if (count>N)
		printf("Error!!!!!!!!!!!\n");
}

}

void* consumer(void *ptr)
{
	srand(time(NULL));
	int item,i;
    while (1) {

	while (count == 0)
		; // wait
	sleep(rand()%2);
	item = buffer[out];
	printf("Remove: %d\n",item);
	out = NEXT(out);
	count--;
	if (count<0)
		printf("Error!!!!!!!!!!!\n");

}
}


int main(void)
{
    long i = 0;
    int err;

    sem_init(&mutex, 0, 1);
    sem_init(&items, 0, 0);
    sem_init(&space, 0, N);



   pthread_create(&tid[0], NULL, consumer, NULL);
   pthread_create(&tid[1], NULL, consumer, NULL);
   pthread_create(&tid[2], NULL, producer, NULL);


    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    
    return 0;
}

