#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	4

void *BusyWork(void *t)
{
   long i, tid;
   double result=0.0;
   tid = (long)t;
   sleep(2);
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++) {
     result = result + sin(i) * tan(i);
     }
   printf("Thread %ld done. Result = %e\n",tid, result);
}

int main(int argc, char *argv[])
{
pthread_t thread[NUM_THREADS];
int rc; 
long t;

for(t=0;t<NUM_THREADS;t++) {
   printf("Main: creating thread %ld\n", t);
   rc = pthread_create(&thread[t], NULL, BusyWork, (void *)t); 
   if (rc) {
     printf("ERROR; return code from pthread_create() is %d\n", rc);
     exit(-1);
     }
  }

printf("Main: program completed. Exiting.\n");
}

