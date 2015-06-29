#如果已经定义了KERNELRELEASE，则说明是从内核构造系统调用的，
#因此可利用其内建语句.
ifneq ($(KERNELRELEASE) , )
	obj-m := atomic.o
#否则，直接从命令行调用，
#这时要调用内核构造系统.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default:
	make -C $(KERNELDIR) M=$(PWD) modules

endif
	
