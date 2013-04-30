ifneq ($(KERNELRELEASE),)
	obj-m := ^PROJECTNAME^_bus_out.o ^PROJECTNAME^_dev_out.o ^PROJECTNAME^_drv_out.o
	^PROJECTNAME^_bus_out-objs := ^PROJECTNAME^_bus.o
	^PROJECTNAME^_dev_out-objs := ^PROJECTNAME^_dev.o
	^PROJECTNAME^_drv_out-objs := ^PROJECTNAME^_drv.o
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
