//#include <studio.h>
#include<unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>

int  main()
{          
 int mycall=syscall(332);
 //printk("call:",syscall); 
 return 0;
}
