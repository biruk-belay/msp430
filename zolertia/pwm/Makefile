CC = msp430-gcc

ifeq ($(MCU), ZOLERTIA)
board = msp430f2617
else
ifeq ($(MCU), TMOTE)
board = msp430f1611 
endif
endif

CFLAGS = -mmcu=$(board)
CFLAGS += -I$(CURDIR)/include
CFLAGS += -D$(MCU)
CFLAGS += -g

BINARY = first
BINARY_HEX = first.ihex
SRC = $(CURDIR)/src/*

OBJ_CPY = msp430-objcopy
CPY_FLAG = --output-target=ihex

INSTALL = tos-bsl
INSTALL_TRGT := --z1
TEMP_VAR ?= $(INSTALL_TRGT)
INSTALL_FLAG = -c /dev/ttyUSB0 -r -e -I -p 
BIN = $(BINARY_HEX:.ihex=.ihex.out)

all:
	$(CC) -o $(BINARY) $(CFLAGS) $(SRC)

install: $(BINARY)
	$(OBJ_CPY) $(CPY_FLAG) $(BINARY) $(BINARY_HEX)
	cp $(BINARY_HEX) $(BIN)
	$(INSTALL) $(INSTALL_TRGT) $(INSTALL_FLAG) $(BIN)
	#rm -f $(BINARY) $(BINARY_HEX)
	mv $(BIN) $(BINARY) $(BINARY_HEX) bin/
	
.PHONY: clean
clean: 
	rm -f bin/*
	rm -f $(BINARY) $(BINARY_HEX)
