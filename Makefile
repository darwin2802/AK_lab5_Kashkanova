obj-m := hello1.o hello2.o

KDIR ?= $(HOME)/repos/linux-4.19.300

ccflags-y += -I$(PWD)/inc/

all:
  $(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
  $(MAKE) -C $(KDIR) M=$(PWD) clean
