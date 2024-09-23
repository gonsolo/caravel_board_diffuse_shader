
TOOLCHAIN_PATH=/home/gonsolo/Downloads/riscv32-elf-ubuntu-22.04-gcc-nightly-2024.09.03-nightly/riscv/bin/
TOOLCHAIN_PREFIX=riscv32-unknown-elf

# ---- Test patterns for project raven ----

.SUFFIXES:

PATTERN = blink

hex:  ${PATTERN:=.hex}

%.elf: %.c ../sections.lds ../crt0_vex.S
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc -I../ -I../generated/ -O0 -mabi=ilp32 -march=rv32i_zicsr -D__vexriscv__ -Wl,-Bstatic,-T,../sections.lds,--strip-debug -ffreestanding -nostdlib -o $@ ../crt0_vex.S ../isr.c $<
	${TOOLCHAIN_PATH}$(TOOLCHAIN_PREFIX)-objdump -D blink.elf > blink.lst

%.hex: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O verilog $< $@
	sed -ie 's/@1000/@0000/g' $@

%.bin: %.elf
	$(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy -O binary $< $@

client: client.c
	gcc client.c -o client

flash: blink.hex
	python3 ../util/caravel_hkflash.py blink.hex
	python3 ../util/caravel_hkstop.py

flash2: blink.hex
	python3 ../util/caravel_flash.py blink.hex

# ---- Clean ----

clean:
	rm -f *.elf *.hex *.bin *.vvp *.vcd blink.lst blink.hexe

.PHONY: clean hex all flash

