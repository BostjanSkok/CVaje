/* v11n1.c – vaja znakovni gonilnik*/
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static int opened = 0;


static int my_open(struct inode *i, struct file *f)
{
    opened++;
    printk(KERN_INFO "v11n1: open()\n");
    return 0;
}
static int my_release(struct inode *i, struct file *f)
{
    printk(KERN_INFO "v11n1: close()\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t
                       len, loff_t *off)
{
    printk(KERN_INFO "v11n1: read(%i)\n", opened);
    
    char *msg[128];
    sprintf(msg, "%i", opened);
    int size = strlen(msg);

    if ( *off >= size)
        return 0;
    if ( len > size - *off)
        len = size - *off;
    if ( copy_to_user( buf, msg, len) )
        return -EFAULT;
    *off += len;
    return len;
}
static ssize_t my_write(struct file *f, const char __user *buf,
                        size_t len, loff_t *off)
{
    printk(KERN_INFO "v11n1: write()\n");
    return len;
}
static struct file_operations pugs_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write
};



static int __init v11n1_init(void)/* Constructor */
{
    printk(KERN_INFO "V11N1 registered \n");
    if (alloc_chrdev_region(&first, 0, 3, "v11n1") < 0)
    {
        return -1;
    }
    printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
    if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
    {
        unregister_chrdev_region(first, 1);
        return -1;
    }
    if (device_create(cl, NULL, first, NULL, "mynull") == NULL)
    {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    cdev_init(&c_dev, &pugs_fops);
    if (cdev_add(&c_dev, first, 1) == -1)
    {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    return 0;
}

static void __exit v11n1_exit(void) /* Destructor */
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 3);
    printk(KERN_INFO "V11N1 unregistered \n");

}

module_init(v11n1_init);
module_exit(v11n1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bostjan Skok <bostjanskok2@gmail.com>");
MODULE_DESCRIPTION("Znakovni gonilnik V11N1");