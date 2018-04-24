#include <linux/init.h>           // Macros used to mark up functions e.g. __init __exit
#include <linux/module.h>         // Core header for loading LKMs into the kernel
#include <linux/device.h>         // Header to support the kernel Driver Model
#include <linux/kernel.h>         // Contains types, macros, functions for the kernel
#include <linux/fs.h>             // Header for the Linux file system support
#include <linux/uaccess.h>          // Required for the copy to user function

static int device_file_major_number = 0;
static const char device_name[] = "dummy-driver";
static const char    g_s_Hello_World_string[] = "This is our dummy driver!\0";
static const ssize_t g_s_Hello_World_size = sizeof(g_s_Hello_World_string);
static numberOpens = 0;
static char   message[256] = {0};          
static short  size_of_message;     


static int     device_file_open(struct inode *, struct file *);
static int     device_file_release(struct inode *, struct file *);
static ssize_t device_file_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_file_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations simple_driver_fops = 
{
	.owner   = THIS_MODULE,
	.read    = device_file_read,
	.write	 = device_file_write,
	.release = device_file_release,
	.open 	 = device_file_open,
};


static int register_device(void)
{
		int result = 0;

		printk( KERN_NOTICE "dummy-driver: register_device() is called." );

		result = register_chrdev( 0, device_name, &simple_driver_fops );
		if( result < 0 )
		{
			printk( KERN_WARNING "dummy-driver:  can\'t register \
				character device with errorcode = %i", result );
			return result;
		}

		device_file_major_number = result;
		printk( KERN_NOTICE "dummy-driver: registered character device \
			with major number = %i and minor numbers 0...255"      \
			 , device_file_major_number );

		return 0;
}

void unregister_device(void)
{
	printk( KERN_NOTICE "dummy-driver: unregister_device() is called" );
	if(device_file_major_number != 0)
	{
		unregister_chrdev(device_file_major_number, device_name);
	}
}


static ssize_t device_file_read(struct file *file_ptr
				, char __user *user_buffer
		        	, size_t count
		                , loff_t *position)
{
	printk( KERN_NOTICE "dummy-driver: Device file is read at offset = %i, read bytes count = %u" \
				, (int)*position    						      \
				, (unsigned int)count );					      \

	/* If position is behind the end of a file we have nothing to read */
	if( *position >= g_s_Hello_World_size )
		return 0;

	/* If a user tries to read more than we have, read only 
	as many bytes as we have */
	if( *position + count > g_s_Hello_World_size )
		count = g_s_Hello_World_size - *position;

	if( copy_to_user(user_buffer, g_s_Hello_World_string + *position, count) != 0 )
		return -EFAULT;	

	/* Move reading position */
	*position += count;
	return count;
}

static ssize_t device_file_write(struct file *filep, const char *buffer, size_t len, loff_t *offset){
   sprintf(message, "%s(%zu letters)", buffer, len);   // appending received string with its length
   size_of_message = strlen(message);                 // store the length of the stored message
   printk(KERN_INFO "EBBChar: Received %zu characters from the user\n", len);
   return len;
}

static int device_file_open(struct inode *inodep, struct file *filep){
   numberOpens++;
   printk(KERN_INFO "EBBChar: Device has been opened %d time(s)\n", numberOpens);
   return 0;
}

static int device_file_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "EBBChar: Device successfully closed\n");
   return 0;
}
 

module_init(register_device);
module_exit(unregister_device);

