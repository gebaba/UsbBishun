/**
 * PB4 PB5 PB6 PB7 PB8 PB9
 * 
 * 
 */
#include "keyboard.h"
#include "missing.h"

#include "stm32f10x_conf.h"

/**
 * 扫描键盘
 * 
 * 
 */
static int read(void) {
    GPIO_ResetBits(GPIOB, GPIO_Pin_4);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
    if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)) {
        return KEY_P;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
        return KEY_DELETE;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
        return KEY_NEXT;
    }
    GPIO_SetBits(GPIOB, GPIO_Pin_4);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
    if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)) {
        return KEY_S;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
        return KEY_Z;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
        return KEY_PREVIOUS;
    }
    GPIO_SetBits(GPIOB, GPIO_Pin_4);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);
    if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)) {
        return KEY_H;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) {
        return KEY_N;
    } else if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) {
        return KEY_OK;
    }
    wait(80);
    return -1;
}

/**
 * 读取按键（阻塞）
 *  
 * return: 按键值
 * 
 */
int readKey(void) {
    int key;
    int i = 0;
    while ((key = read()) == -1);
    do {
        if (i < 9) {
            i++;
        } else {
            switch (key) {
            case KEY_DELETE:
                key = KEY_CLEAR;
                break;
            case KEY_OK:
                key = KEY_MODE;
                break;
            case KEY_PREVIOUS:
                key = KEY_ZOOMOUT;
                break;
            case KEY_NEXT:
                key = KEY_ZOOM;
                break;
            }
            while (read() != -1);
            break;
        }
        wait(80);
    } while (read() != -1);
    return key;
}

/**
 * 初始化 
 * 
 */
void initializeKey(void) {
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOB,
        ENABLE
    );
    /**
     * PB4/JTRST 需要复用
     * 
     * 
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}
