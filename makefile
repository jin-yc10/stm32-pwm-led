
MPU = cortex-m3

SRCS =  main.c pwm.c stm32f10x_it.c led.c

PROJ_NAME = pwm_led
OUTPATH = build
OBJPATH = objs
FLOAT_TYPE = soft
ifneq ($(FLOAT_TYPE), hard)
ifneq ($(FLOAT_TYPE), soft)
override FLOAT_TYPE = hard
#override FLOAT_TYPE = soft
endif
endif

BINPATH=~/Development/gcc-arm-none-eabi-4_8-2014q2/bin
ARM_STD_PATH=~/Development/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include
CC = $(BINPATH)/arm-none-eabi-gcc
OBJCOPY=$(BINPATH)/arm-none-eabi-objcopy
SIZE=$(BINPATH)/arm-none-eabi-size
CFLAGS  = -std=gnu99 -g -O2 -Tstm32_flash.ld -w#-Wall
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MPU) #-nostartfiles

ifeq ($(FLOAT_TYPE), hard)
CFLAGS += -fsingle-precision-constant -Wdouble-promotion
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
else
CFLAGS += -msoft-float
endif

vpath %.c ./ ./led ./pwm
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iled -Ipwm -Ilib -Ilib/STM32F10x_StdPeriph_Driver/inc -I./ -I$(ARM_STD_PATH)
CFLAGS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD

SRCS += lib/startup_stm32f10x_hd.s # add startup file to build hd for f107 with 256kb flash

OBJS = $(SRCS:.c=.o)

.PHONY: lib proj

all: lib proj
	$(SIZE) $(OUTPATH)/$(PROJ_NAME).elf

lib:
	$(MAKE) -C lib FLOAT_TYPE=$(FLOAT_TYPE)

proj: 	$(OUTPATH)/$(PROJ_NAME).elf

$(OUTPATH)/$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -Llib -lstm32f10x -lm -lrdimon -lc -lg -lnosys
	$(OBJCOPY) -O ihex $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).bin

clean:
	rm -f *.o
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
	$(MAKE) clean -C lib # Remove this line if you don't want to clean the libs as well
