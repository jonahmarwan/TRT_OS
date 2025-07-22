# $@ = target file
# $< = first dependency
# $^ = all dependencies

OUT_DIR = compiled

all: run

# Ensure output directory exists before anything else
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/kernel.bin: $(OUT_DIR)/kernel_entry.o $(OUT_DIR)/kernel.o $(OUT_DIR)/isr_stubs.o | $(OUT_DIR)
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

$(OUT_DIR)/kernel_entry.o: kernel_entry.asm | $(OUT_DIR)
	nasm kernel_entry.asm -f elf -o $@

$(OUT_DIR)/kernel.o: kernel.c | $(OUT_DIR)
	i686-elf-gcc -ffreestanding -c kernel.c -o $@

$(OUT_DIR)/isr_stubs.o: isr_stubs.asm | $(OUT_DIR)
	nasm isr_stubs.asm -f elf -o $@

$(OUT_DIR)/kernel.dis: $(OUT_DIR)/kernel.bin | $(OUT_DIR)
	ndisasm -b 32 $< > $@

$(OUT_DIR)/bootsect.bin: bootloader.asm | $(OUT_DIR)
	nasm bootloader.asm -f bin -o $@

$(OUT_DIR)/os-image.bin: $(OUT_DIR)/bootsect.bin $(OUT_DIR)/kernel.bin | $(OUT_DIR)
	cat $^ > $@

run: $(OUT_DIR)/os-image.bin
	qemu-system-i386 -fda $<

clean:
	rm -rf $(OUT_DIR)

