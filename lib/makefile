BINPATH=~/Development/gcc-arm-none-eabi-4_8-2014q2/bin

CC=$(BINPATH)/arm-none-eabi-gcc
AR=$(BINPATH)/arm-none-eabi-ar
OBJDIR=./objects
FLOAT_TYPE=soft

###################################################

# Check for valid float argument
ifneq ($(FLOAT_TYPE), hard)
ifneq ($(FLOAT_TYPE), soft)
#override FLOAT_TYPE = hard
override FLOAT_TYPE = soft
endif
endif

###################################################

vpath %.c STM32F10x_StdPeriph_Driver STM32F10x_StdPeriph_Driver/src

CFLAGS  = -g -O2 -Wall
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m3

ifeq ($(FLOAT_TYPE), hard)
CFLAGS += -fsingle-precision-constant -Wdouble-promotion
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
else
CFLAGS += -msoft-float
endif
#CFLAGS += -mfloat-abi=hard
CFLAGS += -ffreestanding -nostdlib
CFLAGS += -I./ -ISTM32F10x_StdPeriph_Driver/inc -I../
CFLAGS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD

#SRCS  = stm32f4_discovery.c
SRCS = misc.c stm32f10x_dma.c stm32f10x_rcc.c stm32f10x_adc.c \
	stm32f10x_exti.c stm32f10x_can.c stm32f10x_flash.c \
	stm32f10x_rtc.c stm32f10x_crc.c stm32f10x_fsmc.c stm32f10x_sdio.c \
	stm32f10x_gpio.c stm32f10x_spi.c \
  	stm32f10x_tim.c \
  	stm32f10x_usart.c \
	stm32f10x_dac.c stm32f10x_i2c.c stm32f10x_wwdg.c \
	stm32f10x_dbgmcu.c stm32f10x_iwdg.c \
	stm32f10x_pwr.c \
	system_stm32f10x.c

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: libstm32f10x.a

all: libstm32f10x.a

$(OBJDIR)/%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libstm32f10x.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) libstm32f10x.a
