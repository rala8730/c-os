#include<linux/init.h>
#include<linux/module.h>

int hello_init(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	//printk(KERN_ALERT "init print\n");
	return 0;
}

void hello_exit(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	//printk(KERN_ALERT "exit print\n");
	//return 0;
}
//execute when the module starts to work 
module_init(hello_init);
//execute when the module gets uninstalled
module_exit(hello_exit);

//What this means is that when the module is getting started, 
//the kernel follows the function pointed to by module_init() 
//and executes that function. Similarly, when the module is 
//uninstalled, the kernel follows the function pointed to by 
//module_exit(), in this case, the function hello_exit().
