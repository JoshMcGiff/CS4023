#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t lock1;


void *PrintHello(void *threadid)
{

   long tid;
   tid = (long)threadid;
   pthread_mutex_lock(&lock1);
   printf("Hello World! It's me, thread #%ld!\n", tid);
   printf("  Part 2 of the message from thread #%ld!\n", tid);
   pthread_mutex_unlock(&lock1);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   
  // read no. of threads as first arg from command line
  int nt = (int) strtol(argv[1], NULL, 10);
  pthread_mutex_init(&lock1, NULL);

   pthread_t threads[nt];
   int rc;
   long t;
   for(t=0; t<nt; t++){

      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
    pthread_mutex_destroy(&lock1);

   /* Last thing that main() should do */
   pthread_exit(NULL);
}

