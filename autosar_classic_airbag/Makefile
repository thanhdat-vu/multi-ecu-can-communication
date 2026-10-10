TARGET = airbag_autosar

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = -mcpu=cortex-m3 -mthumb

CFLAGS = $(CPU) -O0 -g3 -Wall -ffunction-sections -fdata-sections
LDFLAGS = $(CPU) -T linker.ld -Wl,--gc-sections -Wl,-Map=$(TARGET).map --specs=nosys.specs
INCLUDES = \
-IApp \
-ISwc \
-IRte \
-IMcal \
-IEcuAbstraction \
-IServices \
-IConfig \
-IBase \
-IBsw

C_SOURCES = \
$(wildcard App/*.c) \
$(wildcard Swc/*.c) \
$(wildcard Rte/*.c) \
$(wildcard Mcal/*.c) \
$(wildcard EcuAbstraction/*.c) \
$(wildcard Services/*.c) \
$(wildcard Bsw/*.c)

ASM_SOURCES = startup_stm32f103.s

OBJECTS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SIZE) $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.s
	$(CC) $(CPU) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).bin $(TARGET).map