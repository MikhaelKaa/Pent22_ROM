# We only allow compilation on linux!
ifneq ($(shell uname), Linux)
$(error OS must be Linux!)
endif

TARGET = main
CODE_LOCATION = 0x0000
DATA_LOCATION = 0x2000

# Check if all required tools are on the system.
REQUIRED = sdcc sdar sdasz80
K := $(foreach exec,$(REQUIRED),\
    $(if $(shell which $(exec)),,$(error "$(exec) not found. Please install or add to path.")))

# Global settings: folders.
ROOT 		=	$(realpath .)
BUILD_DIR	=	$(ROOT)/build
SRC_DIR		=	$(ROOT)/src

# Globa settings: tools.
CC			=	sdcc
AS			=	sdasz80
CFLAGS		=	--std-c11 -mz80 --debug --nostdinc --no-std-crt0 --nostdinc --nostdlib
ASFLAGS		=	-xlos -g

.PHONY:	all
all:
	# Create build dir.
	mkdir -p $(BUILD_DIR)

	# Compile crt0.s
	# rm $(BUILD_DIR)/crt0.s
	cp $(SRC_DIR)/crt0.s $(BUILD_DIR)/crt0.s
	$(AS) $(ASFLAGS) $(BUILD_DIR)/crt0.s

	# Compile 
	$(CC) -o $(BUILD_DIR)/$(TARGET).rel -c -I$(SRC_DIR) $(CFLAGS) $(SRC_DIR)/main.c
	$(CC) -o $(BUILD_DIR)/print.rel -c $(CFLAGS) $(SRC_DIR)/print.c
	$(CC) -o $(BUILD_DIR)/mem_test.rel -c $(CFLAGS) $(SRC_DIR)/mem_test.c
	$(CC) -o $(BUILD_DIR)/general_sound.rel -c $(CFLAGS) $(SRC_DIR)/general_sound.c
	
	
	# Link both
	$(CC) -o $(BUILD_DIR)/main.ihx \
		-mz80 -Wl -y --code-loc $(CODE_LOCATION) --data-loc $(DATA_LOCATION) \
		--std-c11 -mz80 --debug --no-std-crt0 --nostdinc --nostdlib \
		-Llib -llibsdcc-z80 \
		$(BUILD_DIR)/crt0.rel \
		$(BUILD_DIR)/main.rel \
		$(BUILD_DIR)/print.rel \
		$(BUILD_DIR)/mem_test.rel \
		$(BUILD_DIR)/general_sound.rel \
		
		
	
	# Finally, convert ihx to binary
	sdobjcopy -I ihex -O binary $(BUILD_DIR)/main.ihx $(BUILD_DIR)/main.bin
	
.PHONY: clean
clean:
	# Remoe everything except source files
	rm -f -r $(BUILD_DIR)

.PHONY: flash
flash:
	PCProg.exe COM18 build/main.bin
