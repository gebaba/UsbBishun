/**
 * W25X16
 * 一次读写有长度限制?
 * 
 */
#ifndef _STORAGE_H_
#define _STORAGE_H_

/**
 * 初始化
 * 
 * return: JEDEC ID 
 * 
 */
int initializeSpi(void);

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
int receiveData(char *buf, int bufSize, int startAddress);

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
int sendData(char *buf, int bufSize, int startAddress);

/**
 * 块擦除
 * 
 * startAddress: 起始地址
 * 
 * return: 擦除大小
 * 
 */
int erase(int startAddress);

#endif
