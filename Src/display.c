#include "display.h"
#include "missing.h"

#include "stm32f10x_conf.h"

/**
 * 引脚 PA0 PA1 PA2 PA3
 * 
 * 
 */
#define	SEL_SET GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define	SEL_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define	DAT_SET	GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define	DAT_CLR	GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define	SDI_SET	GPIO_SetBits(GPIOA, GPIO_Pin_1)
#define	SDI_CLR	GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define	SCK_SET	GPIO_SetBits(GPIOA, GPIO_Pin_0)
#define	SCK_CLR	GPIO_ResetBits(GPIOA, GPIO_Pin_0)

/**
 * 向LCD发送
 * 
 * data: 发送的数据
 * 
 * 
 */
static void send(char data) {
    int i;
    for (i = 0; i < 8; i++) {
        SCK_CLR;
        if(data & 0x80) {
            SDI_SET;
        } else {
            SDI_CLR;
        }
        SCK_SET;
        data <<= 1;
    }
}

/**
 * 发送指令
 * 
 * command: 指令
 * 
 */
static void sendCommand(char command) {
    SEL_CLR;
    DAT_CLR;
    send(command);
    SEL_SET;
}

/**
 * 发送数据
 * 
 * data: 发送的数据
 * 
 */
static void sendData(char data) {
    SEL_CLR;
    DAT_SET;
    send(data);
    SEL_SET;
}

/**
 * 屏幕初始化
 * 
 * 
 */
void initializeLcd(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0);
	sendCommand(0xe2);
	wait(100);
	sendCommand(0xa0);
	sendCommand(0xc8);
	sendCommand(0xa2);
	sendCommand(0x2f);
	sendCommand(0x25);
	sendCommand(0x81);
	sendCommand(0x19);
	sendCommand(0x40);
	sendCommand(0xaf);
	draw(0);
}

/**
 * 显示图像
 * 
 * data: 整屏数据
 * 
 */
void draw(char *data) {
    int i;
    int j;
	for(i = 0; i < ROW_MAX; i++) {
		sendCommand(0xb0 + i);
		sendCommand(0x10);
		sendCommand(0x00);
		for(j = 0; j < COL_MAX; j++) {
			sendData(data ? data[i + j * ROW_MAX] : 0x00);
		}
	}
}
