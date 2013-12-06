all: boot1
boot1: boot1.asm boot2
	nasm -l boot1.list -DENTRY=`./getaddr.sh main` boot1.asm
boot2: boot2.exe
	objcopy -S -O binary boot2.exe boot2
boot2.exe: writeScreen.o boot2.o loadDT.o loadSeg.o queue.o run.o control.o outportb.o mutex.o
	ld  -g -Ttext 0x10000 -e main -o boot2.exe writeScreen.o boot2.o run.o queue.o loadDT.o control.o loadSeg.o outportb.o mutex.o
outportb.o: outportb.S
	gcc -g -c -masm=intel -o outportb.o outportb.S
writeScreen.o: writeScreen.S
	gcc -g -c -masm=intel -o writeScreen.o writeScreen.S
loadDT.o: load_dt.S
	gcc -g -c -masm=intel -o loadDT.o load_dt.S
loadSeg.o: load_segments.S
	gcc -g -c -masm=intel -o loadSeg.o load_segments.S
control.o: control.S
	gcc -g -c -masm=intel -o control.o control.S
boot2.o: boot2.c	
	gcc -g -c -o boot2.o boot2.c
queue.o: queue.c	
	gcc -g -c -o queue.o queue.c
run.o: run.c
	gcc -g -c -o run.o run.c
mutex.o: mutex.c
	gcc -g -c -o mutex.o mutex.c
clean:
	rm boot2.exe boot2 boot1.list boot1 a.img *.o
install: boot1
	bximage -fd -size=1.44 -q a.img
	mformat a:
	dd if=boot1 of=a.img bs=1 count=512 conv=notrunc
	mcopy -o boot2 a:BOOT2
run: install
	qemu -boot a -fda a.img
runm: 
	qemu -boot a -fda a.img
run.s: install
	qemu -S -s -boot a -fda a.img
