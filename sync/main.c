/* 
compile: 
linux: gcc -g -Wall -pedantic -std=gnu99 main.c -lpthread -o main
win: gcc -g -Wall -pedantic -std=gnu99 main.c -o main

note:
"lpthread" must be after the c code for Linux
pthread_mutex_lock blocks 2nd thread from executing, 2nd thread is put to sleep until mutex_unlock
without mutex_lock, shared resource (e.g. "counter" global variable) gets modified by 2nd thread before 1st is done

result:
[0.000042] trythis() starts     -> thread 1
[0.000146] after mutex_lock     -> thread 1
Job 1 has started               -> thread 1
[0.000047] trythis() starts     -> thread 2, cannot execute due to mutex, thread 2 is put to sleep
Job 1 has finished              -> thread 1
[6.478078] before mutex_unlock  -> thread 1
[6.478086] trythis() ends       -> thread 1
[6.478113] after mutex_lock     -> thread 2, awake and start due to mutex_unlock
Job 2 has started               -> thread 2
Job 2 has finished              -> thread 2
[12.951743] before mutex_unlock -> thread 2
[12.951747] trythis() ends      -> thread 2
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
    clock_gettime(CLOCK,&time2);
    printf("[%lf] trythis() starts\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    pthread_mutex_lock(&lock); 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] after mutex_lock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    unsigned long i = 0; 
    counter += 1; 
    printf("Job %d has started\n", counter); 
  
    for(i=0; i<(0xFFFFFFFF);i++); 
  
    printf("Job %d has finished\n", counter); 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] before mutex_unlock\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    pthread_mutex_unlock(&lock); 

    clock_gettime(CLOCK,&time2);
    printf("[%lf] trythis() ends\n", time2.tv_sec - time1.tv_sec + (double)((time2.tv_nsec -time1.tv_nsec)/1000000000.0));

    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while(i < 2) 
    { 
        clock_gettime(CLOCK,&time1);
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
        if (error != 0) 
            printf("\nThread can't be created :[%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
} 