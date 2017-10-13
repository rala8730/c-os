

#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h>
#include<linux/slab.h>
#include<asm/uaccess.h>

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */


ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
    /* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
    /* length is the length of the userspace buffer*/
    /* offset will be set to current position of the opened file after read*/
    /* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */
    
    return 0;
}



ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
    /* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
    /* length is the length of the userspace buffer*/
    /* current position of the opened file*/
    /* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
    
    return length;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
    //*pinode=actual physical file on the hard disk
    //pfile=the abstract open file that contains all the necessary file operations in the file_operations structure
    
    /* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
    //pdf says only print the count not the log file
    count++;
    printk(KERN_ALERT"number of times device has been opened:%d\n",count);
    return 0;
}

int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
    /* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
    count++;
    printk(KERN_ALERT"number of times device has been closed:%d\n",count);
    return 0;
}

loff_t simple_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
    /* Update open file position according to the values of offset and whence */
    return 0;
}

struct file_operations simple_char_driver_file_operations = {
    
    .owner   = THIS_MODULE,
    /* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
    //function pointers (.open, .close, .llseek, .read, .write) are pointing to the five functions for these operations.
    .open=simple_char_driver_open,
    .close=simple_char_driver_close,
    .llseek=simple_char_driver_seek,
    .read=simple_char_driver_read,
    .write=simple_char_driver_write,
};

static int simple_char_driver_init(void)
{
    /* print to the log file that the init function is called.*/
    /* register the device */
    register_chrdev(major_number,name_of_driver,*simple_char_driver_file_operations);
    return 0;
}

static int simple_char_driver_exit(void)
{
    /* print to the log file that the exit function is called.*/
    /* unregister  the device using the register_chrdev() function. */
    unregister_chrdev(major_number,name_of_driver);
    return 0;
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
