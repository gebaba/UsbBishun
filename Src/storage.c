/**
 * 引脚 PA4 PA5 PA6 PA7[SPI1]
 * 
 * 
 */
#include "storage.h"

#include "stm32f10x_conf.h"

#define	SEL_SET GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define	SEL_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_4)

#ifndef USE_SPI1

#define	SCK_SET GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define	SCK_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define	SDO_SET GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define	SDO_CLR GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define	SDI_GET GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)

#endif

/**
 * 发送或者接收数据
 * 
 * data: DUMMY-0xA5 要发送的数据
 * 
 * return: 接收到的数据
 * 
 */
static char send(char data) {
#ifndef USE_SPI1
    int r = 0;
    int i;
    for (i = 0; i < 8; i++) {
        SCK_CLR;
        if (data & 0x80) {
            SDO_SET;
        } else {
            SDO_CLR;
        }
        data <<= 1;
        SCK_SET;
        r <<= 1;
        if (SDI_GET) {
            r |= 1;
        }
        SCK_CLR;
    }
    return r;
#else
    while (SPI_I2S_GetFlagStatus(
        SPI1,
        SPI_I2S_FLAG_TXE
    ) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
#endif
}

/**
 * 初始化
 * 
 * return: JEDEC ID 
 * 
 */
int initializeSpi(void) {
    int id;
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA,
        ENABLE
    );
#ifndef USE_SPI1
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
#else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    {
        SPI_InitTypeDef SPI_InitStruct;
        SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
        SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
        SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStruct.SPI_CRCPolynomial = 7;
        SPI_Init(SPI1, &SPI_InitStruct);
        SPI_Cmd(SPI1, ENABLE);
    }
#endif
    SEL_SET;
    SEL_CLR;
    send(0x9f);
    id = (send(0xff) << 16) | (send(0xff) << 8) | (send(0xff));
    SEL_SET;
    return id;
}

/**
 * 读数据
 * 
 * buf: 数据缓冲区
 * bufSize: 缓冲区大小
 * startAddress: 起始地址
 * 
 * return: 读到的数量
 * 
 */
int receiveData(char *buf, int bufSize, int startAddress) {
    int i;
    SEL_CLR;
    send(0x03);
    send((startAddress & 0xff0000) >> 16);
    send((startAddress & 0xff00) >> 8);
    send((startAddress & 0xff));
    for (i =  0; i < bufSize; i++) {
        buf[i] = send(0xff);
    }
    SEL_SET;
    return bufSize;
}

/**
 * 写数据
 * 
 * buf: 数据缓冲区
 * bufSize: 缓冲区大小
 * startAddress: 起始地址
 * 
 * return: 写入的数量
 * 
 */
int sendData(char *buf, int bufSize, int startAddress) {
    int i;
    SEL_CLR;
    send(0x06);
    SEL_SET;
    /**
     * 写使能
     * 
     * 
     */
    SEL_CLR;
    send(0x02);
    send((startAddress & 0xFF0000) >> 16);
    send((startAddress & 0xFF00) >> 8);  
    send((startAddress & 0xFF));
    for (i =  0; i < bufSize; i++) {
        send(buf[i]);
    }
    SEL_SET;
    /**
     * 等待写结束
     * 
     * 
     */
    SEL_CLR;
    send(0x05);
    while (send(0xff) & 0x01);
    SEL_SET;
    return bufSize;
}


/**
 * 块擦除
 * 
 * startAddress: 起始地址
 * 
 * return: 擦除大小
 * 
 */
int erase(int startAddress) {
    SEL_CLR;
    send(0x06);
    SEL_SET;
    SEL_CLR;
    send(0x01);
    send(0x00);
    send(0x00);
    SEL_SET;
    SEL_CLR;
    send(0x05);
    while (send(0xff) & 0x01);
    SEL_SET;
    /**
     * 擦除之前要清除写保护状态
     * 
     * 
     */
    SEL_CLR;
    send(0x06);
    SEL_SET;
    SEL_CLR;
    send(0x20);
    send((startAddress & 0xFF0000) >> 16);
    send((startAddress & 0xFF00) >> 8);  
    send((startAddress & 0xFF));
    SEL_SET;

    SEL_CLR;
    send(0x05);
    while (send(0xff) & 0x01);
    SEL_SET;
    return 4096;
}
