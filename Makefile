obj-m += scull.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc p3.c -o main.o
	gcc p2.c -o p2.o
	gcc p1.c -o p1.o

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	cat /dev/null > /dev/scull0
	cat /dev/null > /dev/scull1
sign:
	/usr/src/linux-headers-6.2.0-36-generic/scripts/sign-file sha256 ~/keys/key1/MOK.priv ~/keys/key1/MOK.pem ./scull.ko
