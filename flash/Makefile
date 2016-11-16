CC = msp430-gcc
MCU = msp430f1611
CFLAGS = -mmcu=$(MCU)
CFLAGS += -I$(CURDIR)/include

BINARY = first
BINARY_HEX = first.ihex
SRC = $(CURDIR)/src/*

OBJ_CPY = msp430-objcopy
CPY_FLAG = --output-target=ihex

INSTALL = tos-bsl
INSTALL_TRGT = --telosb
INSTALL_FLAG = -c /dev/ttyUSB0 -r -e -I -p 

#SOURCE = $(SRC_DIR$(wildcard *.c))
BIN = $(BINARY_HEX:.ihex=.ihex.out)


all:
	$(CC) -o $(BINARY) $(CFLAGS) $(SRC)


install: $(BINARY)
	$(OBJ_CPY) $(CPY_FLAG) $(BINARY) $(BINARY_HEX)
	cp $(BINARY_HEX) $(BIN)
	$(INSTALL) $(INSTALL_TRGT) $(INSTALL_FLAG) $(BIN)
	#rm -f $(BINARY) $(BINARY_HEX)
	#mv $(BIN) $(BINARY) $(BINARY_HEX) bin/
	
.PHONY: clean
clean: 
	rm -f bin/*
	rm -f $(BINARY) $(BINARY_HEX)
