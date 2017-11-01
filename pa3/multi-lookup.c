#include<stdio.h>
#include<stdlib.h>
#include "multi-lookup.h"

copyfile(char source[], char dest[]){
  int c;
  FILE *f1 = fopen(source, "r");
  FILE *f2 = fopen(dest, "w");
  while((c = fgetc(f1)) != EOF){
    fputc(c, f2);
  }
  fclose(f1);
  fclose(f2);
}

void resolver_func(){
    
    
}

void requester_func(){
    
    
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
    printf("%s \n",argv[2]);//num of resolver thread
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
    copyfile(argv[5],"copytest.txt");    
    
    
    return 0;
}
