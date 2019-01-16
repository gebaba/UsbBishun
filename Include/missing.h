/**
 * 内存管理
 * 
 * 
 */
#ifndef _MISSING_H_
#define _MISSING_H_

/**
 * 获取字符串长度
 * 
 * string: 字符串
 * 
 * return: 字符串长度
 * 
 */
int strlen(char *string);

/**
 * 分配内存 
 *
 * size: 大小
 * 
 * return: 分配到的指针
 * 
 */
void *malloc(int size);

/**
 * 拷贝
 * 
 * dest: 目标位置
 * data: 源
 * size: 大小
 * 
 * return: 目标位置
 * 
 */
void *memcpy(void *dest, void *data, int size);

/**
 * 释放内存
 * 
 * ptr: 内存
 * 
 */
void free(void *ptr);

/**
 * 等待
 * 
 * miliseconds: 毫秒
 * 
 */
void wait(unsigned int miliseconds);

#endif
