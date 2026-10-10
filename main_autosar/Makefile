PROJECT := main_node_autosar_lite_f407

CC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy

CFLAGS := -mcpu=cortex-m4 -mthumb -O0 -g3 \
          -ffreestanding -fdata-sections -ffunction-sections \
          -Wall -Wextra

INCLUDES := -IBase -IConfig -IServices -IBsw -IMcal \
            -IEcuAbstraction -IRte -ISwc -IApp

LDFLAGS := -T linker.ld \
           -Wl,--gc-sections \
           -nostartfiles \
           -specs=nosys.specs \
           -specs=nano.specs

SRCS := App/main.c \
        Bsw/EcuM.c \
        Bsw/BswM.c \
        Bsw/CanIf.c \
        Bsw/CanIf_PBcfg.c \
        Bsw/PduR.c \
        Bsw/PduR_PBcfg.c \
        Services/OsIf.c \
        Services/Det.c \
        Services/SchM.c \
        Mcal/Adc.c \
        Mcal/I2c.c \
        Mcal/Mcu.c \
        Mcal/Uart.c \
        Mcal/Dio.c \
        Mcal/Can.c \
        Mcal/Can_PBcfg.c \
        EcuAbstraction/LcdIf.c \
        EcuAbstraction/ComIf.c \
        Rte/Rte_Main.c \
        Swc/MainNodeS.c \
        Swc/MainNodeS_Data.c

OBJS := $(SRCS:.c=.o) startup_stm32f407.o

all: $(PROJECT).elf $(PROJECT).bin

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

startup_stm32f407.o: startup_stm32f407.s
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(PROJECT).elf $(PROJECT).bin main_node_autosar_split.elf main_node_autosar_split.bin
