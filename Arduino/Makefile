DEVICE = atmega328p
CLOCK = 16000000UL
PORT = /dev/ttyACM0
BAUD = 115200 
AVR_COMPILE = avr-gcc
AVR_COPY = avr-objcopy
AVR_UPLOAD = avrdude

HEADERS_DIR = headers
SRC_DIR = src
OBJ_DIR = obj
EXECUTABLE = arduino

RM = rm

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: clean build upload

build:
	$(AVR_COMPILE) -I $(HEADERS_DIR) -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -o $(OBJ_DIR)/$(EXECUTABLE).elf $(SRC_FILES)
	$(AVR_COPY) -j .text -O ihex $(OBJ_DIR)/$(EXECUTABLE).elf $(OBJ_DIR)/$(EXECUTABLE).hex

upload:
	$(AVR_UPLOAD) -v -p $(DEVICE) -c arduino -P $(PORT) -b $(BAUD) -U flash:w:$(OBJ_DIR)/$(EXECUTABLE).hex:i 

.PHONY: clean
clean:
	$(RM) ./$(OBJ_DIR)/*
