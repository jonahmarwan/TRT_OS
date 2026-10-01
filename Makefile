# $@ = target file
# $< = first dependency
# $^ = all dependencies

OUT_DIR = compiled

all: run

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/os-image.bin: $(OUT_DIR)/bootsect.bin $(OUT_DIR)/kernel.bin | $(OUT_DIR)
	cat $^ > $@

run: $(OUT_DIR)/os-image.bin
	qemu-system-i386 -fda $<

clean:
	rm -rf $(OUT_DIR)

