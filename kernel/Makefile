OUT_DIR = ../compiled
all: $(OUT_DIR)/kernel.bin $(OUT_DIR)/kernel.dis

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/kernel.bin: $(OUT_DIR)/kernel_entry.o $(OUT_DIR)/kernel.o $(OUT_DIR)/isr_stubs.o | $(OUT_DIR)
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

$(OUT_DIR)/kernel_entry.o: ../boot/kernel_entry.asm | $(OUT_DIR)
	nasm ../boot/kernel_entry.asm -f elf -o $@

$(OUT_DIR)/kernel.o: kernel.c | $(OUT_DIR)
	i686-elf-gcc -ffreestanding -c kernel.c -o $@

$(OUT_DIR)/isr_stubs.o: isr_stubs.asm | $(OUT_DIR)
	nasm isr_stubs.asm -f elf -o $@

$(OUT_DIR)/kernel.dis: $(OUT_DIR)/kernel.bin | $(OUT_DIR)
	ndisasm -b 32 $< > $@

clean:
	rm -rf $(OUT_DIR)