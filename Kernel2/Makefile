# Makefile – makefile of our first driver
 
# if KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq (${KERNELRELEASE},)
	obj-m := v12n1.o
# Otherwise we were called directly from the command line.
# Invoke the kernel build system.
else
	KERNEL_SOURCE := /lib/modules/3.8.0-25-generic/build
	PWD := $(shell pwd)
default:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules
  
clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
endif