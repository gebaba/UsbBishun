/**
 * JoyStickMouse 工程中的 usb_desc.c 内容替换
 * 
 * 
 */
#include "usb_keyboard.h"
#include "missing.h"

#include "usb_lib.h"

#define KEYBOARD_VID 0x17EF
#define KEYBOARD_PID 0x6018

const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] = {
    0x12, // bLength
    USB_DEVICE_DESCRIPTOR_TYPE, // bDescriptorType (DEVICE_DESCRIPTOR)
    0x10, 0x01, // bcdUSB (USB 1.1)
    0x00, // bDeviceClass
    0x00, // bDeviceSubClass
    0x00, // bDeviceProtocol
    0x08, // bMaxPacketSize
    KEYBOARD_VID & 0xFF, (KEYBOARD_VID >> 8) & 0xFF,
    KEYBOARD_PID & 0xFF, (KEYBOARD_PID >> 8) & 0xFF,
    0x13, 0x01, // bcdDevice
    0x01, // Index of string descriptor describing manufacturer
    0x02, // Index of string descriptor describing product
    0x00, // Index of string descriptor describing the device serial number
    0x01  // bNumConfigurations
};

const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] = {
    0x09, // bLength: Configuration Descriptor size
    USB_CONFIGURATION_DESCRIPTOR_TYPE, // bDescriptorType: (CONFIGURATION_DESCRIPTOR)
    JOYSTICK_SIZ_CONFIG_DESC, 0x00, // wTotalLength: Bytes returned
    0x01, // bNumInterfaces: 1 interface
    0x01, // bConfigurationValue: Configuration value
    0x00, // iConfiguration: Index of string descriptor describing the configuration
    0x80, // bmAttributes: (BUS_POWERED) 
    0x32, // MaxPower 100 mA: this current is used for detecting Vbus

    0x09, // bLength: Interface Descriptor size
    USB_INTERFACE_DESCRIPTOR_TYPE, // bDescriptorType: (INTERFACE_DESCRIPTOR)
    0x00, // bInterfaceNumber: Number of Interface
    0x00, // bAlternateSetting: Alternate setting
    0x01, // bNumEndpoints
    0x03, // bInterfaceClass: HID
    0x01, // bInterfaceSubClass : 1=BOOT, 0=no boot
    0x01, // nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse
    0x00, // iInterface: Index of string descriptor

    0x09, // bLength: HID Descriptor size
    HID_DESCRIPTOR_TYPE, // bDescriptorType: HID
    0x10, // bcdHID: HID Class Spec release number
    0x01,
    0x00, // bCountryCode: Hardware target country
    0x01, // bNumDescriptors: Number of HID class descriptors to follow
    0x22, // bDescriptorType
    JOYSTICK_SIZ_REPORT_DESC, 0x00, // wItemLength: Total length of Report descriptor
    
    0x07, // bLength: Endpoint Descriptor size
    USB_ENDPOINT_DESCRIPTOR_TYPE, // bDescriptorType:
    0x81, // bEndpointAddress: Endpoint Address (IN)
    0x03, // bmAttributes: Interrupt endpoint
    0x08, 0x00, // wMaxPacketSize: 8 Byte max 
    0x0a // bInterval: Polling Interval (10 ms)
};

const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop) 
    0x09, 0x06, // USAGE (Keyboard) 
    0xa1, 0x01, // COLLECTION (Application) 
    0x05, 0x07, // USAGE_PAGE (Keyboard) 
    0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl) 
    0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI) 
    0x15, 0x00, // LOGICAL_MINIMUM (0) 
    0x25, 0x01, // LOGICAL_MAXIMUM (1) 
    0x75, 0x01, // REPORT_SIZE (1) 
    0x95, 0x08, // REPORT_COUNT (8) 
    0x81, 0x02, // INPUT (Data,Var,Abs) 
    0x95, 0x01, // REPORT_COUNT (1) 
    0x75, 0x08, // REPORT_SIZE (8) 
    0x81, 0x03, // INPUT (Cnst,Var,Abs) 
    0x95, 0x06, // REPORT_COUNT (6) 
    0x75, 0x08, // REPORT_SIZE (8) 
    0x15, 0x00, // LOGICAL_MINIMUM (0) 
    0x25, 0x65, // LOGICAL_MAXIMUM (101) 
    0x05, 0x07, // USAGE_PAGE (Keyboard) 
    0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated)) 
    0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application) 
    0x81, 0x00, // INPUT (Data,Ary,Abs) 
    0xc0 // END_COLLECTION 
};

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] = {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
}; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] = {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    'L', 0, 'i', 0, 't', 0, 'e', 0, '-', 0, 'O', 0, 'n', 0, ' ', 0, 'T', 0, 'e', 0, 'c', 0, 'h', 0, 'n', 0, 'o', 0, 'l', 0, 'o', 0, 'g', 0, 'y', 0, ' ', 0, 'C', 0, 'o', 0, 'r', 0, 'p', 0, '.', 0
};

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] = {
    JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'L', 0, 'e', 0, 'n', 0, 'o', 0, 'v', 0, 'o', 0, ' ', 0, 'U', 0, 'S', 0, 'B', 0, ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0
};

uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] = {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE        /* bDescriptorType */
};

__IO uint8_t PrevXferComplete = 1;

int plugedIn = 0;

static RESULT Class_NoData_Setup(uint8_t RequestNo) {
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))) {
        if (RequestNo == SET_PROTOCOL) {
            return Joystick_SetProtocol();
        } else if (RequestNo == SET_IDLE) {
            plugedIn = 1;
            return USB_SUCCESS;
        }
    }
    return USB_UNSUPPORT;
}

/**
 * 发送数据
 * 
 * data: 要发送的数据
 * 
 * 
 */
static void send(unsigned char *data, unsigned int size) {
    PrevXferComplete = 0;
    USB_SIL_Write(EP1_IN, data, size);
    SetEPTxValid(ENDP1);
    {
        int i = 0;
        while (!PrevXferComplete) {
            if (i++ > 100) {
                plugedIn = 0;
                break;
            }
            wait(10);
        }
    }
}

/**
 * 初始化 
 * 
 * 
 */
void initializeUsb(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA,
        ENABLE
    );
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    {
        NVIC_InitTypeDef NVIC_InitStruct;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
        NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
        NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStruct);
    }
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
    /**
     * fix
     * 
     * 
     */
    Device_Property.Class_NoData_Setup = Class_NoData_Setup;
    Device_Property.MaxPacketSize = 8;
    USB_Init();
}

/**
 * 按键消息
 * 
 * key: 按键消息 [A-Z+-]
 * 
 */
void sendKey(char key) {
    unsigned char buf[8] = {0};
    /**
     * 00 00 xx xx 第1、2字节是特殊按键 shift：0x02，ctrl：0x01
     * 'A'~'Z': 0x04~0x1d
     * -_: 0x2d
     * +=: 0x2e
     * 
     * 
     */
    if (plugedIn) {
        if ('a' <= key && key <= 'z') {
            buf[2] = 4 + key - 'a';
        } else if (key == '-') {
            buf[0] = 1;
            buf[2] = 0x2d;
        } else if (key == '+') {
            buf[0] = 1;
            buf[2] = 0x2e;
        }
        send(buf, sizeof(buf));
        buf[0] = 0;
        buf[2] = 0;
        send(buf, sizeof(buf));
    }
}
