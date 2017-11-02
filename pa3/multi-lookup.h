#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

char source[] = "track.txt";
pthread_mutex_t hostLock;

void* reqhelp();
void copyfile(char source[]);
void resolver_func(int thrds);
void requester_func(int thrds);
/*
struct thread_info {
  pthread_t thread_id;
  int thread_num;
  char *argv_string;
};
*/
