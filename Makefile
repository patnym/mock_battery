obj-m += mockbattery.o

#This defaults your own kernel, change this to if not building towards the building systems kernel
KSRC ?= /lib/modules/$(shell uname -r)/build/

CROSS_COMPILE ?=

all:
	make CROSS_COMPILE=$(CROSS_COMPILE) -C $(KSRC) M=$(PWD) modules
clean: 
	make -C $(KSRC) M=$(PWD) clean
