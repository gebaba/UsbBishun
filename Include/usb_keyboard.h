/**
 * 键盘
 * 
 */
#ifndef _USBKEYBOARD_H_
#define _USBKEYBOARD_H_

#include "stm32f10x.h"

#define USB_DEVICE_DESCRIPTOR_TYPE        0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE 0x02
#define USB_STRING_DESCRIPTOR_TYPE        0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE     0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE      0x05

#define HID_DESCRIPTOR_TYPE               0x21
#define JOYSTICK_SIZ_HID_DESC             0x09
#define JOYSTICK_OFF_HID_DESC             0x12

#define JOYSTICK_SIZ_DEVICE_DESC          18
#define JOYSTICK_SIZ_CONFIG_DESC          34
#define JOYSTICK_SIZ_REPORT_DESC          45
#define JOYSTICK_SIZ_STRING_LANGID        4
#define JOYSTICK_SIZ_STRING_VENDOR        50
#define JOYSTICK_SIZ_STRING_PRODUCT       40
#define JOYSTICK_SIZ_STRING_SERIAL        2

#define STANDARD_ENDPOINT_DESC_SIZE       0x09

extern const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC];
extern const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];
extern const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC];
extern const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID];
extern const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR];
extern const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT];
extern uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL];

/**
 * 初始化 
 * 
 * 
 */
void initializeUsb(void);

/**
 * 按键消息
 * 
 * key: 按键消息 [A-Z+-]
 * 
 */
void sendKey(char key);

#endif
