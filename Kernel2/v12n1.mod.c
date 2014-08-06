#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x9a31bb74, "module_layout" },
	{ 0xb7c59293, "cdev_del" },
	{ 0x37a0cba, "kfree" },
	{ 0xd61adcbd, "kmem_cache_alloc_trace" },
	{ 0x5cd9dbb5, "kmalloc_caches" },
	{ 0xf3248a6e, "class_destroy" },
	{ 0x27e3ef6b, "device_destroy" },
	{ 0xebd1da60, "cdev_add" },
	{ 0xaa4fb4f8, "cdev_init" },
	{ 0xd4f29297, "device_create" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x25827ecd, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x27e1a049, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "109A680AA9A680A6982B034");
