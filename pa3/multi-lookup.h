#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"

char source[] = "track.txt";
pthread_mutex_t hostLock;
pthread_mutex_t queueLock;
pthread_mutex_t resLock;
sem_t mutex;
char *temp;

void* reqhelp();
void* reshelp();
void copyfile(char source[]);
void resolver_func(int rthrds);
void requester_func(int thrds);
