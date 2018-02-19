obj-m += mockbattery.o

#This defaults your own kernel, change this to if not building towards the building systems kernel
ifeq ($(KSRC),) 
KSRC := /lib/modules/$(shell uname -r)/build/
endif

ifeq ($(CC),) 
CC := gcc
endif

all:
	make $(CC) -C $(KSRC) M=$(PWD) modules
clean: 
	make $(CC) -C $(KSCR) M=$(PWD) clean