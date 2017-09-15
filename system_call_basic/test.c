//#include <studio.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include<stdlib.h>
int  main()
{          
 int mycall=syscall(332);
 
 int number1=1;
 int number2=2;
 int *result=malloc(sizeof(int));
 int mycall_simple_one=syscall(333,number1,number2,&result);
// printk(KERN_ALERT,"mysyscall)simple_one: %d\n",mycall_simple); 
//printk("call:",syscall); 
 return 0;
}
