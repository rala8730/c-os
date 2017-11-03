#include "multi-lookup.h"
#include "queue.h"
#include <unistd.h>
#include <string.h>

queue buffer;
queue* resbuffer = &buffer;
/////////////////////////////
int queue_init(queue* q, int size){                                
  int i;
  q->maxSize = size;
  q->array = malloc(sizeof(queue_node) * (q->maxSize));
  if(!(q->array)){
    perror("Error on queue Malloc");
    return QUEUE_FAILURE;
  }
  for(i=0; i < q->maxSize; ++i){
    strcpy(q->array[i].payload, "");
    q->array[i].used = 0;
  }
  /* setup circular buffer values */
  q->front = 0;
  q->rear = 0;
  return q->maxSize;
}                                                                  
                                                                     
int queue_is_empty(queue* q){                                      
  if((q->front == q->rear) && (q->array[q->front].used == 0)){ 
    return 1;                                                          
  }                                                                  
  else{                                                              
    return 0;                                                          
  }                                                                  
}                                                                  
                                                                     
int queue_is_full(queue* q){
  if((q->front == q->rear) && (q->array[q->front].used != 0)){
    return 1;
  }
  else{
    return 0;
  }
}

char* queue_pop(queue* q){                                         
  temp = malloc(sizeof (char) * 1030);
  if(queue_is_empty(q)){
    return NULL;
  }
  strcpy(temp, q->array[q->front].payload);
  strcpy(q->array[q->front].payload, "");
  q->array[q->front].used = 0;
  q->front = ((q->front + 1) % q->maxSize);                          
  return temp;
}
                                                                     
int queue_push(queue* q, char* new_payload){
  if(queue_is_full(q)){
    return QUEUE_FAILURE;
  }
  printf("%s", new_payload);
  strcpy(q->array[q->rear].payload, new_payload);
  q->array[q->rear].used = 1;
  q->rear = ((q->rear+1) % q->maxSize);
  return QUEUE_SUCCESS;
}

void queue_cleanup(queue* q){
  while(!queue_is_empty(q)){
    queue_pop(q);
  }
  free(q->array);
  pthread_mutex_destroy(&queueLock);
  sem_destroy(&mutex);
}


/////////////////////////////
void* reshelp(){
  printf("reshelp");
  sem_wait(&mutex);
  pthread_mutex_lock(&queueLock);
  //
  char temp[1030];
  strcpy(temp, queue_pop(resbuffer));
  printf("%s", temp);
  pthread_mutex_unlock(&queueLock);
  return 0;
}

void* reqhelp(){
  pthread_mutex_lock(&hostLock);
  FILE *f  = fopen(source, "r");
  FILE *fp = fopen("temp.txt", "w");
  int dLine = 0;
  int lineN = 0;
  int c;
  char test[1030];
  rewind(f);
  while((c = fgetc(f)) != EOF){
    if(lineN != 0){
      fputc(c, fp);
    }else{
      test[dLine] = c;
      dLine++;
    }
    if(c == '\n'){
      lineN++;
    }
  }
  fclose(f);
  fclose(fp);
  remove(source);
  rename("temp.txt", source);
  pthread_mutex_unlock(&hostLock);
  if(strcmp(test, "") != 0){
    //printf("%s . I am %lu \n",test, pthread_self());
    //printf("%s",test);
    pthread_mutex_lock(&queueLock);
    while(queue_is_full(&buffer)){
      usleep(rand() % 100 + 5);
      printf("is full");
    }
    //printf("%s", test);
    queue_push(&buffer, test);
    pthread_mutex_unlock(&queueLock);
    sem_post(&mutex);
  }
  FILE *tf = fopen(source,"r");
  int tc;
  if((tc = fgetc(tf)) != EOF){
    reqhelp();
  }
  fclose(tf);
  return 0;
}

void copyfile(char file[]){
  int c;
  FILE *f1 = fopen(file, "r");
  FILE *f2 = fopen(source, "w");
  while((c = fgetc(f1)) != EOF){
    fputc(c, f2);
  }
  fclose(f1);
  fclose(f2);
}

void resolver_func(int rthrds){
  pthread_t rtid[rthrds];
  printf("h");
  printf("n =  \n");
  printf("h");
  int i = 0;
  int err;
  while (i <rthrds){
    err = pthread_create(&(rtid[i]), NULL, &reshelp, NULL);
    if(err !=0){
      printf("err resolver_func");
    }
    i++;
  }
  i=0;
  while(i < rthrds){
    pthread_join(rtid[i],NULL);
    i++;
  }
  free(temp);
  pthread_mutex_destroy(&resLock);
}

void requester_func(int thrds){
  
  pthread_t tid[thrds];
  printf("n = %d \n",thrds);
  int i = 0;
  int err;
  while (i <thrds){
    err = pthread_create(&(tid[i]), NULL, &reqhelp, NULL);
    if(err !=0){
      printf("err requester_func");
    }
    i++;
  }
  i=0;
  while(i < thrds){
    pthread_join(tid[i],NULL);
    i++;
  }
  pthread_mutex_destroy(&hostLock);
}

int main(int argc, char **argv ){
    //printing the argument
    printf("%s \n",argv[1]);//num of requester thread
    int reqThrds = atoi(argv[1]);
    int resThrds = atoi(argv[2]);
    printf("%s \n",argv[2]);//num of resolver thread
    printf("%s \n",argv[3]);//result.txt
    printf("%s \n",argv[4]);//service.txt
    printf("%s \n",argv[5]);//name1.txt
    printf("%s \n",argv[6]);//name2.txt
    printf("%s \n",argv[7]);//name3.txt
    printf("%s \n",argv[8]);//name4.txt
    printf("%s \n",argv[9]);//name5.txt
    
    //test copy
    queue_init(&buffer, 50);

    copyfile(argv[5]);
    sem_init(&mutex,0,1);
    requester_func(reqThrds);
    resolver_func(resThrds);
    queue_cleanup(&buffer);
    return 0;
}
