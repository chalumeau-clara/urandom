KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
target = epidriver
obj-m := epidriver.o
epidriver-objs := src/driver.o src/random.o


modules: $(OBJS)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $@ $^

modules_install: $(OBJS)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) $@ $^

clean:
	$(RM) src/*.o *.o *~ core .depend src/.*.cmd .*.cmd *.ko *.mod.c *.tmp_versions *.mod *.order *.symvers

load:
	@-sudo rmmod $(target)
	@sudo dmesg -C
	@sudo insmod $(target).ko
	@sudo dmesg

load_param:
	@-sudo rmmod $(target)
	@sudo dmesg -C
	@echo sudo insmod $(target).ko alphabet=\"\"
	@echo sudo dmesg

unload:
	@sudo rmmod $(target)

nod:
	@echo sudo mknod /dev/epirandom c major 0

.PHONY: modules modules_install clean test load load_param unload nod
