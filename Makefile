# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard kernel/*.c utils/*.cpp drivers/*.c cpu/*.c)
CPP_SOURCES = $(wildcard kernel/*.cpp utils/*.cpp)
HEADERS = $(wildcard includes/*.h)
OBJ_FILES = $(wildcard kernel/*.o)

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: boot/kernel_entry.o kernel/kernel.o io.o idt.o idt_flush.o interrupts.o
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os-image.bin: boot/mbr.bin kernel.bin
	cat $^ > $@

io.o: utils/io.cpp
	x86_64-elf-g++ -g -m32 -ffreestanding -c $< -o $@ # -g for debugging
	
idt.o: cpu/idt.cpp
	x86_64-elf-g++ -g -m32 -ffreestanding -c $< -o $@ # -g for debugging

idt_flush.o: cpu/idt_flush.asm
	nasm -felf32 $^ -o $@

interrupts.o: cpu/interrupts.asm
	nasm -felf32 $^ -o $@

run: os-image.bin
	qemu-system-i386 -fda $<

echo: os-image.bin
	xxd $<

# only for debug
kernel.elf: boot/kernel_entry.o ${OBJ_FILES}
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin -d guest_errors,int &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.cpp
	x86_64-elf-g++ -g -m32 -ffreestanding -c $< -o $@ # -g for debugging

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

clean:
	$(RM) *.bin *.o *.dis *.elf
	$(RM) kernel/*.o
	$(RM) boot/*.o boot/*.bin
	$(RM) drivers/*.o
	$(RM) cpu/*.o
