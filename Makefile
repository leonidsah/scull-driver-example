obj-m += scull.o

all:
	#sudo make rm
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc p3.c -o main.o
	gcc p2.c -o p2.o
	gcc p1.c -o p1.o
	sudo make sign
	sudo make load
	sudo make create

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	cat /dev/null > /dev/scull0
	cat /dev/null > /dev/scull1
sign:
	/usr/src/linux-headers-6.2.0-36-generic/scripts/sign-file sha256 ~/keys/key1/MOK.priv ~/keys/key1/MOK.pem ./scull.ko
create:
	sudo mknod /dev/scull0 c $$(cat /proc/devices | awk '/scull/ {print $$1}') 0
	sudo mknod /dev/scull1 c $$(cat /proc/devices | awk '/scull/ {print $$1}') 1
	sudo chmod 777 /dev/scull0
	sudo chmod 777 /dev/scull1
load:
	insmod ./scull.ko
rm:	
	rmmod scull
	rm /dev/scull0 || true
	rm /dev/scull1 || true
