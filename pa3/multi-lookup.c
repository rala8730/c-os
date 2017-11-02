#include "multi-lookup.h"

void* reqhelp(){
  pthread_mutex_lock(&hostLock);
  FILE *f  = fopen(source, "r");
  FILE *fp = fopen("temp.txt", "w");
  int dLine = 1;
  int lineN = 0;
  int c;
  char test;
  rewind(f);
  while((c = fgetc(f)) != EOF){
    if(c == '\n'){
      lineN++;
    }
    if(lineN != dLine){
      fputc(c, fp);
    }else{
      test = test + c;
      printf("%c",c);
    }
  }
  fclose(f);
  fclose(fp);
  remove(source);
  rename("temp.txt", source);
  pthread_mutex_unlock(&hostLock);
  printf("%c \n",test);
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

void resolver_func(int thrds){
        
}

void requester_func(int thrds){
  pthread_t tid[thrds];
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

/*
 Your appliction will take as input a set of name files.
 Names files contain one hostname per line.
 Each name file should be serviced by a single requester thread from the requester thread pool.
 The number of requester threads may be less than or more than the number of input file.
 */
int main(int argc, char **argv ){
    //printing the argument
    printf("%s \n",argv[1]);//num of requester thread
    int reqThrds = *argv[1];
    printf("%s \n",argv[2]);//num of resolver thread
    int resThrds = *argv[2];
    printf("%s \n",argv[3]);//result.txt
    printf("%s \n",argv[4]);//service.txt
    printf("%s \n",argv[5]);//name1.txt
    printf("%s \n",argv[6]);//name2.txt
    printf("%s \n",argv[7]);//name3.txt
    printf("%s \n",argv[8]);//name4.txt
    printf("%s \n",argv[9]);//name5.txt
    
    //read from the file
    /*
    FILE *fp;
    fp=open(argv[5],"r");
    fprint(fp, "testing fprint");
    fputs("testing fputs", fp);
    fclose(fp);
    */
     //pthread_t resolver, requester;
    
    //test copy

    copyfile(argv[5]);    
    requester_func(reqThrds);
    
    return 0;
}
