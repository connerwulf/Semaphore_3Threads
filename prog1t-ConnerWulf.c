#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

/* Student: Conner Wulf. */

//Global Variables
struct rusage mytiming;
struct timeval mytimeval;

struct shared_dat
   {
   int value;     /* shared variable to store result*/
   };

struct shared_dat  *counter;
int getpid();
pthread_mutex_t mutex;
int jumps=0;

/****************************************************************
* This function increases the value of shared variable "counter"
  by one 2750000 times, and by 100 when count-> is a multiple of 100
****************************************************************/
void * thread1(void *arg)
{
	int line = 0;
  int temp = 0;
	while (line < 2750000)
	{

    temp = jumps;
    line++;
    while(pthread_mutex_trylock(&mutex) != 0)
    {
      //Do nothing
    }
      counter->value = counter->value + 1;
	    counter->value = counter->value * 2;
	    counter->value = counter->value / 2;


      if(counter->value % 100 == 0 && counter->value <= 5500000 - 100 && line <= 2750000 - 100)
      {
        counter->value = counter->value + 100;
        line += 100;
        jumps++;
      }
      pthread_mutex_unlock(&mutex);

  }
	printf("from process1 counter  =  %d, jumps %d \n", counter->value, jumps);
  return(NULL);
}


/****************************************************************
This function increases the value of shared variable "counter"
by one 275000 times
****************************************************************/
void * thread2(void *arg)
{
	int line = 0;

	while (line < 2750000)
	{


        line++;
        while(pthread_mutex_trylock(&mutex) != 0)
        {

        }
        /* Critical Section */
	       counter->value = counter->value + 1;
	       counter->value = counter->value * 2;
	       counter->value = counter->value / 2;
         pthread_mutex_unlock(&mutex);
  

   }
	   printf("from process2 counter = %d\n", counter->value);
return(NULL);
}

/****************************************************************
*                  Main Body                                    *
****************************************************************/
int main()
{
  int r=0;
	int i;
  pthread_t	tid1[1];     /* process id for thread 1 */
  pthread_t	tid2[1];     /* process id for thread 2 */
  //pthread_t	tid3[1];     /* process id for thread 2 */
  pthread_attr_t	attr[1];     /* attribute pointer array */

	pthread_mutex_init(&mutex,NULL);
  counter = (struct shared_dat *) malloc(sizeof(struct shared_dat));

	/* initialize shared memory to 0 */
	counter->value = 0;
  printf("1 - I am here %d in pid %d\n",r,getpid());

	fflush(stdout);
 /* Required to schedule thread independently.
 Otherwise use NULL in place of attr. */
  pthread_attr_init(&attr[0]);
  pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);  /* system-wide contention */

	/* end to schedule thread independently */

/* Create the threads */

  pthread_create(&tid2[0], &attr[0], thread2, NULL);
  pthread_create(&tid1[0], &attr[0], thread1, NULL);


/* Wait for the threads to finish */
  pthread_join(tid2[0], NULL);
  pthread_join(tid1[0], NULL);



	printf("from parent counter  =  %d\n", counter->value);
  getrusage(RUSAGE_SELF, &mytiming);
  printf("Time used is sec: %d, usec %d\n",mytiming.ru_utime.tv_sec,mytiming.ru_utime.tv_usec);
  printf("System Time used is sec: %d, usec %d\n",mytiming.ru_stime.tv_sec,mytiming.ru_stime.tv_usec);
	printf("---------------------------------------------------------------------------\n");
	printf("\t\t	End of simulation\n");

	exit(0);

}
