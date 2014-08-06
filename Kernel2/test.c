#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* marsikaj */
#include <linux/errno.h> /* kode napak */
#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/uaccess.h> /* copy_*_user */
#define SC1_MAJOR 0
#define SC1_QUANTUM_SIZE 10
#define SC1_QSET_SIZE 5
#define DEVICE_NAME "sc1"
#define use
_
cdev 0
//#define use_cdev 1
MODULE_LICENSE("GPL");
struct sc1_dev {
void **data;
u
nsigned quantum
_
size;
unsigned qset_size;
unsigned size;
struct cdev cdev;
};
int sc1_trim(struct sc1_dev *dev);
int sc1
_
open(struct inode *inode, struct file *filp);
int sc1_release(struct inode *inode, struct file *filp);
ssize_t sc1_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
ssize_t sc1_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);
struct file_operations sc1_fops = {
.owner = THIS_MODULE,
.
llseek = NULL,
.read = sc1_read,
.write = sc1_write,
.ioctl = NULL,
.open = sc1_open,
.release = sc1_release,
};
int sc1_major = SC1_MAJOR;
int sc1_minor = 0;
struct sc1_dev *sc1_dev_ptr;

int sc1_trim(struct sc1_dev *dev)
{
int i;
if (d
>dt){
if
(d
ev-
>d
a
t
a
)
{
for (i = 0; i < dev->qset_size; i++)
if (dev->data[i])
kfree(dev->data[i]);
kfree(dev
-
>data);
kfree(dev
>data);
dev->data = NULL;
}
dev->size = 0;
r
eturn 0;
}
int sc1_open(struct inode *inode, struct file *filp)
{
struct sc1_dev *dev;
#if use_cdev
dev = container_of(inode->i_cdev, struct sc1_dev, cdev);
#else
dev sc1 dev ptr; // tudi zgoraj lahko takole
dev
=
sc1_dev_ptr;
//
tudi
zgoraj
lahko
takole
#endif
filp->private_data = dev;
if ( (filp
-
>f flags & O ACCMODE)
==
O WRONLY)
if
(
(filp
>f_flags
&
O_ACCMODE)
O_WRONLY)
sc1_trim(dev);
return 0;
}
int sc1_release(struct inode *inode, struct file *filp)
{ return 0; }

ssize_t sc1_read(struct file *
filp, char __user *buf, size
_t count, loff_t *f_pos)
{
struct sc1 dev
*
dev
=
filp
-
>private data;
struct
sc1_dev
dev
filp
>private_data;
int quantum_size
= dev->quantum_size;
int qset_size = dev->qset_size;
int s_pos, q_pos;
ssize_t retval = 0;
if (*f_pos >= dev->size)
goto out;
if ( count > dev->size - *f_pos)
td
>i
*f
coun
t
=
d
ev
-
>
s
i
ze
-
*f_
pos;
s_pos = (long)*f_pos / quantum_size;
q_pos = (long)*f_pos % quantum_size;
// beremo le do
konca trenutnega kvanta
if (count > quantum_size - q_pos)
count = quantum_size - q_pos;
if ( copy_to_user(buf, dev->data[s_po
s] + q_pos, count)) {
retval = -EFAULT;
goto out;
}
*f + t
*f_
pos
+
= coun
t
;
retval = count;
out:
return retval;
return
retval;
}


ssize_t sc1_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
struct sc1_dev *dev = filp->private_data;
int quantum_size = dev->quantum_size;
int qset size
=
dev
-
>qset size;
int
qset_size
dev
>qset_size;
int s_pos, q_pos;
ssize_t retval = -ENOMEM;
printk(KERN_INFO "sc1: write offset = %ld", (long)*f_pos);
s pos = (long)*f pos / quantum size;
// pozicija v kvantni mnozici
s_pos
=
(long)*f_pos
/
quantum_size;
//
pozicija
v
kvantni
mnozici
q_pos = (long)*f_pos % quantum_size; // pozicija v kvantu
if ( s_pos >= qset_size)
return count; // st. kvantov je omejeno na qset_size
//lkijkt i(t)
//
a
l
o
k
ac
ij
a
k
van
t
ne mnoz
i
ce
(
qse
t)
if (!dev->data) {
dev->data = kmalloc(qset_size * sizeof(char *), GFP_KERNEL);
if (!dev->data) goto out;
memset(dev->data, 0, qset_size * sizeof(char *));
}
if (!dev
-
>
data[s
_
pos]) {
dev->data[s_pos] = kmalloc(quantum_size * sizeof(char), GFP_KERNEL);
if (!dev->data[s_pos]) goto out;
}
if (count > quantum_size - q_pos) // pisemo le do konca trenutnega kvanta
count = quantum_size - q_pos;
if (copy_from_user( dev->data[s_pos] + q_pos, buf, count)) {
retval = -EFAULT;
goto out;
}
*f_pos += count;
retval = count;
// posodobimo velikost
if (dev->size < *f_pos)
d
ev->size = *f
p
os
;
_p ;
out:
return retval;
}

void sc1_cleanup_module(void)
{
if (sc1_dev_ptr) {
sc1
_
trim(sc1
_
dev
_
ptr);
#if use_cdev
cdev_del(& sc1_dev_ptr->cdev);
#endif
kfree(sc1 dev ptr);
kfree(sc1_dev_ptr);
}
#if use_cdev
de
v
t
de
vn
o
= MKDEV
(sc
1m
ajo
r
,
sc
1min
o
r
);
de _t de o (sc _ ajo , sc _ o );
unregister_chrdev_region(devno, 1);
#else
unregister_chrdev(sc1_m
ajor, DEVICE_NAME);
#endif
}
#if use_cdev
static void sc1_setup_c
dev(struct sc1_dev *dev)
{
{
int err, devno = MKDEV(
sc1_major, sc1_minor);
cdev_init(&dev->cdev, &sc1_fops);
dev
-
>cdev.owner
=
THIS MODULE;
dev
cdev.owner
THIS_MODULE;
dev->cdev.ops = &sc1_fops;
err = cdev_add(&dev->cdev, devno, 1);
if (err)
printk(KERN_NOTICE "Error %d
adding sc1", err);
}
#endif


int sc1_init_module(void)
{
int result;
#if use_cdev
dev_t dev = 0;
if (sc1_major) { dev = MKDEV(sc1_major, sc1_minor); result = register_chrdev_region(dev, 1, DEVICE_NAME); }
else { result = alloc_chrdev_region(&dev, sc1_minor, 1, DEVICE_NAME); sc1_major = MAJOR(dev); }
if( lt<0){
i tk(KERN WARNING " 1 '
ttj%d
\
"1j)
tlt
}
if
(
resu
lt
<
0)
{
pr
i
n
tk(KERN
_
WARNING
"
sc
1
: can
't
ge
t
ma
j
or
%d
\
n
"
, sc
1
_ma
j
or
)
;
r
e
t
urn resu
lt
;
}
#else
sc1_major = register_chrdev(sc1_major, DEVICE_NAME, &sc1_fops);
if (sc1_major < 0) { printk(KERN_ALERT "Registracija znakovne naprave spodletela.\n"); return sc1_major; }
sc1_minor = 0;
#endif
printk(KERN_INFO "sc1: major %d, minor %d\n", sc1_major, sc1_minor);
sc1 dev
p
tr = kmalloc
(
sizeof
(
struct sc1 dev
),
GFP KERNEL
);
__
p((
_
),
_
);
if (!sc1_dev_ptr) { result = -ENOMEM; goto fail; }
memset(sc1_dev_ptr, 0, sizeof(struct sc1_dev));
sc1_dev_ptr->quantum_size = SC1_QUANTUM_SIZE; sc1_dev_ptr->qset_size = SC1_QSET_SIZE;
#if use_cdev
sc1_setup_cdev(sc1_dev_ptr);
#endif
return 0;
fail:
sc1_cleanup_module();
return result;
}
module_init(sc1_init_module); module_exit(sc1_cleanup_module);