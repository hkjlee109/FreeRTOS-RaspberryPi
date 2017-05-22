ARCH := armv7-a
CPU := cortex-a7
TARGET := kernel7

BUILD_DIR := build
FREERTOS_DIR := FreeRTOS
APPLICATION_DIR := Application

TOOLCHAIN_PREFIX := arm-none-eabi-

AS := $(TOOLCHAIN_PREFIX)as
CC := $(TOOLCHAIN_PREFIX)gcc
LD := $(TOOLCHAIN_PREFIX)ld
OBJDUMP := $(TOOLCHAIN_PREFIX)objdump
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy

ASFLAGS := -march=$(ARCH) -mcpu=$(CPU) -mfloat-abi=hard -mfpu=neon-vfpv4
CFLAGS := -march=$(ARCH) -mtune=$(CPU) -mfloat-abi=hard -mfpu=neon-vfpv4
CFLAGS += -I$(FREERTOS_DIR)/include -I$(APPLICATION_DIR) -I$(FREERTOS_DIR)/portable/GCC/ARM_CA15

C_SRC_FILES = Application/main.c

ASM_SRC_FILES = Application/start.s

C_OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o,$(C_SRC_FILES))
ASM_OBJECTS = $(patsubst %.s, $(BUILD_DIR)/%.o,$(ASM_SRC_FILES))

all: $(TARGET).img

$(TARGET).img: $(TARGET).elf
	$(OBJCOPY) -O binary $^ $@

$(TARGET).elf: $(C_OBJECTS) $(ASM_OBJECTS)
	$(LD) $^ -static -Map $(TARGET).map -T Application/application.ld -o $@

clean:
	rm $(C_OBJECTS) $(ASM_OBJECTS) *.elf *.bin

debug:
	@echo
	@echo "Target Source files:"
	@echo $(SRC_FILES)
	@echo "Target Object files:"
	@echo $(OBJECTS)

.PHONY: all clean debug

$(BUILD_DIR)/%o: %s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%o: %c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<
