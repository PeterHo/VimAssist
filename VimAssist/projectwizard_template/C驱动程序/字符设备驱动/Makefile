ifneq ($(KERNELRELEASE),)
	obj-m := ^PROJECTNAME^_out.o
	^PROJECTNAME^_out-objs := ^PROJECTNAME^.o
else
	KERNELDIR := /home/goodhzz/src/linux-2.6.38
	PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order
install:
	cp *.ko ~/rootfs
endif
