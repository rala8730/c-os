

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<asm/uaccess.h>

#define BUFFER_SIZE 1024
//#define major_number 240
//#define name_of_driver "simple_char_device"

/* Define device_buffer and other global data structures you will need here */

int opencount=0;
int closecount=0;
char device_buffer[BUFFER_SIZE];

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
    /* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
    /* length is the length of the userspace buffer*/
    /* offset will be set to current position of the opened file after read*/
    /* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
	//buffer=destination
	//source= device_buffer
	//size=length
	printk(KERN_ALERT,"copying data");
	copy_to_user(buffer,device_buffer,length);
	printk(KERN_ALERT,"copied data: %d",length);
    
    return 0;
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
    /* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
    /* length is the length of the userspace buffer*/
    /* current position of the opened file*/
    /* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	printk(KERN_ALERT,"writing data");	
	*offset = strlen(&device_buffer[0]);	
	copy_from_user(buffer, device_buffer,length);
	printk(KERN_ALERT,"written data: %d",length);
    
    return length;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
    //*pinode=actual physical file on the hard disk
    //pfile=the abstract open file that contains all the necessary file operations in the file_operations structure
    
    /* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
    //pdf says only print the count not the log file
    opencount++;
    printk(KERN_ALERT"number of times device has been opened:%d\n",opencount);
    return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
    /* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
    closecount++;
    printk(KERN_ALERT"number of times device has been closed:%d\n",closecount);
    return 0;
}

loff_t simple_char_driver_llseek (struct file *pfile, loff_t offset, int whence)
{
    /* Update open file position according to the values of offset and whence */
	//loff_t f_pos;
	switch (whence){
		//the current position is set to the value of the offset.
		case 0: 
		pfile->f_pos=offset;
		break;
		//the current position is incremented by offset bytes 
		case 1:
		pfile->f_pos=pfile->f_pos+offset;
		break;
		//the current position is set to offset bytes before the end of the file.
		case 2:pfile->f_pos=device_buffer-offset;
		break;	
	}
    return 0;
}

struct file_operations simple_char_driver_file_operations = {
    
    .owner   = THIS_MODULE,
    /* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
    //function pointers (.open, .close, .llseek, .read, .write) are pointing to the five functions for these operations.
    .open=simple_char_driver_open,
    .release=simple_char_driver_close,
    .llseek=simple_char_driver_llseek,
    .read=simple_char_driver_read,
    .write=simple_char_driver_write,
};

static int simple_char_driver_init(void)
{
    /* print to the log file that the init function is called.*/
    /* register the device */
	printk(KERN_ALERT "Entering simple character device\n");
	void *__kmalloc(size_t size, gfp_t GFP_KERNAL);
    	register_chrdev(240,"simple_char_device",&simple_char_driver_file_operations);
    return 0;
}

static int simple_char_driver_exit(void)
{
    /* print to the log file that the exit function is called.*/
    /* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "Exiting simple character device \n");
	unregister_chrdev(240,"simple_char_device");
	void kfree(device_buffer);
    return 0;
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
