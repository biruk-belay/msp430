CC = msp430-gcc
MCU = msp430f1611
CFLAGS = -mmcu=$(MCU) -s
OUT_PUT = first
OUT_PUT_HEX = first.ihex
OBJ_CPY = msp430-objcopy
CPY_FLAG = --output-target=ihex
INSTALL = tos-bsl
INSTALL_TRGT = --telosb
INSTALL_FLAG = -c /dev/ttyUSB0 -r -e -I -p 

SOURCE = $(wildcard *.c)
BIN = $(OUT_PUT_HEX:.ihex=.ihex.out)


all:
	$(CC) -o $(OUT_PUT) $(CFLAGS) $(SOURCE)


install: $(OUT_PUT)
	$(OBJ_CPY) $(CPY_FLAG) $(OUT_PUT) $(OUT_PUT_HEX)
	cp $(OUT_PUT_HEX) $(BIN)
	$(INSTALL) $(INSTALL_TRGT) $(INSTALL_FLAG) $(BIN)
	rm -f $(OUT_PUT_HEX)
	mv $(BIN) bin/

.PHONY: clean
clean: 
	rm -f bin/*
