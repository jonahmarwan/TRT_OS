OUT_DIR = ../compiled

all: $(OUT_DIR)/bootsect.bin

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/bootsect.bin: bootloader.asm | $(OUT_DIR)
	nasm bootloader.asm -f bin -o $@

clean:
	rm $(OUT_DIR)/bootsect.bin