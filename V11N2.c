/* v11n1.c – Our First Driver code */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
 
static int __init v11n1_init(void) /* Constructor */
{
    printk(KERN_INFO "V11N1 registered");
    return 0;
}
 
static void __exit v11n1_exit(void) /* Destructor */
{
    printk(KERN_INFO "V11N1 unregistered");
}
 
module_init(v11n1_init);
module_exit(v11n1_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bostjan Skok <bostjanskok2@gmail.com>");
MODULE_DESCRIPTION("Znakovni gonilnik V11N1");`