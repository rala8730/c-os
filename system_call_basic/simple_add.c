#include<linux/kernel.h>
#include<linux/linkage.h>
asmlinkage long sys_simple_add(int number1,int number2,int *result)
{
 *result=number1+number2;
 printk(KERN_ALERT"number1 : %d\n",number1);
 printk(KERN_ALERT"number2 : %d\n",number2);
 printk(KERN_ALERT"myreasult : %d\n",*result);
return 0;
}

