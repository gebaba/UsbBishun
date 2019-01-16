# 
# Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-gdb.exe bs_usb.elf
# (gdb) target remote localhost:2331
# (gdb) load
#

_DEBUG = 1

CC = Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-gcc
LD = Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-ld
AS = Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-as
CP = Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-objcopy
AR = Tools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/bin/arm-none-eabi-ar

LDFLAGS = -TSTM32F103C8T6_FLASH.ld -LTools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/arm-none-eabi/lib -LTools/gcc-arm-none-eabi-5_4-2016q3-20160926-win32/lib/gcc/arm-none-eabi/5.4.1

CXXFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O0 -nostartfiles -ffunction-sections -fdata-sections -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -IInclude -ITools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport -ITools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -ITools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/inc -ITools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/inc

# CXXFLAGS += -DINITIALIZE_STORAGE

ifeq ($(_DEBUG), 1)
	CXXFLAGS += -g -gdwarf-2
endif

OBJECTS = display.o \
	graph.o \
	ime.o \
	keyboard.o \
	main.o \
	missing.o \
	storage.o \
	trie_storage.o \
	usb_keyboard.o \
	system_stm32f10x.o \
	stm32f10x_it.o \
	startup_stm32f10x_md.o \
	core_cm3.o \
	usb_endp.o usb_istr.o usb_prop.o usb_pwr.o hw_config.o

STM32F10X_STDPERIPH_DRIVER_OBJECTS = misc.o \
	stm32f10x_adc.o \
	stm32f10x_bkp.o \
	stm32f10x_can.o \
	stm32f10x_cec.o \
	stm32f10x_crc.o \
	stm32f10x_dac.o \
	stm32f10x_dbgmcu.o \
	stm32f10x_dma.o \
	stm32f10x_exti.o \
	stm32f10x_flash.o \
	stm32f10x_fsmc.o \
	stm32f10x_gpio.o \
	stm32f10x_i2c.o \
	stm32f10x_iwdg.o \
	stm32f10x_pwr.o \
	stm32f10x_rcc.o \
	stm32f10x_rtc.o \
	stm32f10x_sdio.o \
	stm32f10x_spi.o \
	stm32f10x_tim.o \
	stm32f10x_usart.o \
	stm32f10x_wwdg.o

STM32_USB-FS-DEVICE_OBJECTS = usb_core.o \
	usb_init.o \
	usb_int.o \
	usb_mem.o \
	usb_regs.o \
	usb_sil.o

all: $(OBJECTS) libSTM32F10x_StdPeriph_Driver.a libSTM32_USB-FS-Device.a
	$(LD) -o bs_usb.elf $(OBJECTS) libSTM32F10x_StdPeriph_Driver.a libSTM32_USB-FS-Device.a $(LDFLAGS)
	$(CP) -O ihex bs_usb.elf bs_usb.hex
display.o: src/display.c
	$(CC) -c src/display.c $(CXXFLAGS)
graph.o: src/graph.c
	$(CC) -c src/graph.c $(CXXFLAGS)
ime.o: src/ime.c
	$(CC) -c src/ime.c $(CXXFLAGS)
keyboard.o: src/keyboard.c
	$(CC) -c src/keyboard.c $(CXXFLAGS)
main.o: src/main.c
	$(CC) -c src/main.c $(CXXFLAGS)
missing.o: src/missing.c
	$(CC) -c src/missing.c $(CXXFLAGS)
storage.o: src/storage.c
	$(CC) -c src/storage.c $(CXXFLAGS)
trie_storage.o: src/trie_storage.c
	$(CC) -c src/trie_storage.c $(CXXFLAGS)
usb_keyboard.o: src/usb_keyboard.c
	$(CC) -c src/usb_keyboard.c $(CXXFLAGS)
system_stm32f10x.o: src/system_stm32f10x.c
	$(CC) -c src/system_stm32f10x.c $(CXXFLAGS)
stm32f10x_it.o: src/stm32f10x_it.c
	$(CC) -c src/stm32f10x_it.c $(CXXFLAGS)
startup_stm32f10x_md.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s
	$(AS) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s -mcpu=cortex-m3 -mthumb -g -gdwarf-2 -o startup_stm32f10x_md.o
core_cm3.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.c $(CXXFLAGS)
usb_endp.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_endp.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_endp.c $(CXXFLAGS)
usb_istr.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_istr.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_istr.c $(CXXFLAGS)
usb_prop.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_prop.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_prop.c $(CXXFLAGS)
usb_pwr.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_pwr.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Projects/JoyStickMouse/src/usb_pwr.c $(CXXFLAGS)
hw_config.o: src/hw_config.c
	$(CC) -c src/hw_config.c $(CXXFLAGS)

libSTM32F10x_StdPeriph_Driver.a: $(STM32F10X_STDPERIPH_DRIVER_OBJECTS)
	$(AR) cr libSTM32F10x_StdPeriph_Driver.a $(STM32F10X_STDPERIPH_DRIVER_OBJECTS)
misc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c $(CXXFLAGS)
stm32f10x_adc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c $(CXXFLAGS)
stm32f10x_bkp.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c $(CXXFLAGS)
stm32f10x_can.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c $(CXXFLAGS)
stm32f10x_cec.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c $(CXXFLAGS)
stm32f10x_crc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c $(CXXFLAGS)
stm32f10x_dac.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c $(CXXFLAGS)
stm32f10x_dbgmcu.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c $(CXXFLAGS)
stm32f10x_dma.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c $(CXXFLAGS)
stm32f10x_exti.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c $(CXXFLAGS)
stm32f10x_flash.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c $(CXXFLAGS)
stm32f10x_fsmc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c $(CXXFLAGS)
stm32f10x_gpio.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c $(CXXFLAGS)
stm32f10x_i2c.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c $(CXXFLAGS)
stm32f10x_iwdg.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c $(CXXFLAGS)
stm32f10x_pwr.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c $(CXXFLAGS)
stm32f10x_rcc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c $(CXXFLAGS)
stm32f10x_rtc.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c $(CXXFLAGS)
stm32f10x_sdio.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c $(CXXFLAGS)
stm32f10x_spi.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c $(CXXFLAGS)
stm32f10x_tim.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c $(CXXFLAGS)
stm32f10x_usart.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c $(CXXFLAGS)
stm32f10x_wwdg.o: Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
	$(CC) -c Tools/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c $(CXXFLAGS)

libSTM32_USB-FS-Device.a: $(STM32_USB-FS-DEVICE_OBJECTS)
	$(AR) cr libSTM32_USB-FS-Device.a $(STM32_USB-FS-DEVICE_OBJECTS)
usb_core.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_core.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_core.c $(CXXFLAGS)
usb_init.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_init.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_init.c $(CXXFLAGS)
usb_int.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_int.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_int.c $(CXXFLAGS)
usb_mem.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_mem.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_mem.c $(CXXFLAGS)
usb_regs.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_regs.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_regs.c $(CXXFLAGS)
usb_sil.o: Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_sil.c
	$(CC) -c Tools/STM32_USB-FS-Device_Lib_V4.1.0/Libraries/STM32_USB-FS-Device_Driver/src/usb_sil.c $(CXXFLAGS)

.PHONY:
clean:
	rm -f $(OBJECTS) bs_usb.elf bs_usb.hex $(STM32F10X_STDPERIPH_DRIVER_OBJECTS) libSTM32F10x_StdPeriph_Driver.a $(STM32_USB-FS-DEVICE_OBJECTS) libSTM32_USB-FS-Device.a
