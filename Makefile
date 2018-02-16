obj-m += mockbattery.o

#This defaults your own kernel, change this to if not building towards the building systems kernel
ifeq ($(KERNEL_SRC),) 
KERNEL_SRC := /lib/modules/$(shell uname -r)/build/
endif

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules
clean: 
	make -C $(KERNEL_SRC) M=$(PWD) clean