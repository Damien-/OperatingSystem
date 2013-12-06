OperatingSystem
===============

Kernel


Tools used:

•	Bximage. This utility will build a virtual floppy disk (a file called a.img) for you.
 
•	The dd copy utility. You will use this utility to copy your stage 1 boot loader to the virtual floppy.
 
•	The mtools suite of utilities, specifically mcopy. You will use this utility to copy your stage 2 OS to the virtual floppy.
 
•	The Qemu x86 emulator. Your will use this emulator to run, and test your operating system.
 
•	GDB, the Gnu Debugger.  You will use this tool to debug your operating system.
 
•	The nasm assembler. You will use this assembler to generate the stage 1 boot loader and the object code for the clearScr() and writeScr() function in the stage 2 OS code.
 
•	gcc, the Gnu C compiler. You will use the cross compiler to generate object code for the main driver of your stage 2 operating system.
 
•	objcopy, the object code translator. You will use objcopy to strip out all symbolic information from the stage 2 OS code.
 
•	Debian, a distribution of Linux.   You can use another distribution if you wish.  You will, however be on your own in getting things to work.
 
•	VirtualBox, a free but commercial grade emulator.  You need VirtualBox only if you are not booting Debian Linux natively.  VirtualBox will allow you to run Debian Linux under Windows (XP, Vista, or 7), Mac OS X, or another distribution of Linux without having to install Linux on your hard drive is a separate partition.  At the end of the class, if you do not want to keep Linux, you can simple delete the virtual machine and uninstall VirtualBox.


Skills learnt:
•	Using the qemu emulator and the DDD debugger to run and debug  OS 
•	Compiling a boot loader and the OS 
•	Installing your boot loader and OS 
•	Writing to the screen 
•	Memory management as joint effor of hardware and software
•	Setting up the Global Descriptor Table (GDT)
•	Software stack-based process switching 
•	Setting up the Interrupt Vector Table (IDT) 
•	Writing and installing fault handlers 
•	Writing and installing a service routine for task switching 
•	Investigating how race conditions can create security issues
•	Creating mutexes
•	Using mutexes 


