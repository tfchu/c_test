/* 
# gcc -g -Wall -pedantic -std=gnu99 mutex2.c -lpthread -o main

note:
mutex_lock between 3 threads: main (thread 0), Job1 (thread 1), and Job2 (thread 2)
main mutex_lock first so Job1/Job2 are blocked and put to sleep until main mutex_unlock
then Job1 mutex_lock so Job2 is blocked and is put to sleep until Job1 mutex_unlock
then Job2 mutex_lock, runs and mutex_unlock

result:
[0.000000] before mutex_lock        // before main thread mutex_lock
[0.000105] after mutex_lock         // after main thread mutex_lock, both Job1 and Job2 are put to sleep
[6.619601] before mutex_unlock      // before main thread mutex_unlock, unlock happens right after this
[6.619623] Job 1 has started        // Job1 starts, mutex_lock again so Job2 is put to sleep
[6.619624] after mutex_unlock       // main thread continues to run
[6.621401] Job 1 has finished       // Job1 ends and mutex_unlock, Job2 is woken
[6.621438] Job 2 has started        // Job2 starts and mutex_lock
[6.623081] Job 2 has finished       // Job2 ends
*/
#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<time.h>

#define CLOCK CLOCK_REALTIME
struct timespec time1,time2;

pthread_t tid[2]; 
int counter; 
pthread_mutex_t lock; 

void* trythis(void *arg) 
{ 
    pthread_mutex_lock(&lock); 
    unsigned long i = 0; 
    counter += 1; 
    clock_gettime(CLOCK,&time2);
    printf("[%lf] Job %d has started\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0), counter); 
  
    for(i=0; i<(0xFFFFF);i++); 
    clock_gettime(CLOCK,&time2);
    printf("[%lf] Job %d has finished\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0), counter); 
    pthread_mutex_unlock(&lock); 

    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0, j = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    
    clock_gettime(CLOCK,&time1);

    clock_gettime(CLOCK,&time2);
    printf("[%lf] before mutex_lock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    pthread_mutex_lock(&lock); 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] after mutex_lock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));
    
    for(j=0; j<(0xFFFFFFFF);j++); 
    while(i < 2) 
    { 
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
        if (error != 0) 
            printf("\nThread can't be created :[%s]", strerror(error)); 
        i++; 
    } 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] before mutex_unlock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    pthread_mutex_unlock(&lock); 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] after mutex_unlock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));
    
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
} 