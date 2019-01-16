#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/**
 * STM32_USB-FS-Device_Lib_V4.1.0 中的缺失项
 * 
 * 
 */
#include "stm32f10x.h"

#include "usb_type.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "usb_istr.h"

/**
 * 替换 JoyStickMouse 中的 usb_desc.h
 * 
 * 
 */
#include "usb_keyboard.h"

extern __IO uint8_t PrevXferComplete;

void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);

#endif
