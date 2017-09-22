CSCI 3753 OPERATING SYSTEM

PROGRAMMING ASSIGNMENT 1

NAME:RASMI LAMICHHANE

EMAIL:rala8730@colorado.edi

a. arch/x86/kernel/simple_add.c
This is file contains the implementation system call. We add 2 number and return the result.

b. arch/x86/kernel/Makefile
This is a makefile, it help building helloworld.c and simple_add.c file.(addint to bottom of makefile i.e obj-y+=helloworld.o obj-y+=simple_add.o) 

c. arch/x86/syscalls/syscall_64.tbl
This is system call table of kernal.(adding system call i.e 332    64    helloworld        sys_helloworld  and 333    64    simple_add        sys_simple_add)


d. include/linux/syscalls.h
This is a header file that contains all decelearation of system calls. (add prototype at the bottom of file before endif "asmlinkage long sys_simple_add(int number1, int number2, int *result);")

e. /var/log/syslog
This file is ued to check the message from system call. we can use dmesg too.(no need to edit)


Run:
step1. After adding require line in files and adding simple_add.c file except the test and compile the kernel by following command on your terminal.
	sudo make -j2 CC="ccache gcc"
	sudo make -j2 modules_install
	sudo make -j2 install
	sudo reboot
step2. Add the test file and run it by following command on your terminal.
	gcc test.c
	./a.out
step3:
	dmesg/ got to syslog to see if you did it correctly. If the message is print you did it.

