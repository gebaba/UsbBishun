#include "missing.h"

#include "stm32f10x_conf.h"

/**
 * 简单的内存分配
 * 
 * 
 */
#define MEMORY_MAX 512

unsigned char memory[MEMORY_MAX];

struct Header {
    int size;
    int used;
    unsigned char allocated[1];
};

/**
 * 获取字符串长度
 * 
 * string: 字符串
 * 
 * return: 字符串长度
 * 
 */
int strlen(char *string) {
    int i = 0;
    while (string[i]) i++;
    return i;
}

/**
 * 分配内存 
 *
 * size: 大小
 * 
 * return: 分配到的指针
 * 
 */
void *malloc(int size) {
    int i = 0;
    while (i < MEMORY_MAX) {
        struct Header* header = (struct Header*) &memory[i];
        if (!header->used) {
            if (!header->size) {
                header->size = size;
            }
            if (size > header->size) {
                continue;
            }
            header->used = 1;
            return &header->allocated[0];
        }
        i += sizeof(int) * 2 + header->size;
    }
    return 0;
}

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
void *memcpy(void *dest, void *data, int size) {
    while (size--) {
        ((char *) dest)[size] = ((char *) data)[size];
    }
    return dest;
}

/**
 * 释放内存
 * 
 * ptr: 内存
 * 
 */
void free(void *ptr) {
    if (ptr) {
        char *p = ptr;
        p -= sizeof(int) * 2;
        ((struct Header *) p)->used = 0;
    }
}

/**
 * 等待
 * 
 * miliseconds: 毫秒
 * 
 */
void wait(unsigned int miliseconds) {
    unsigned int i;
    SysTick->LOAD = SystemCoreClock / 8000 * miliseconds;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        i = SysTick->CTRL;
    } while ((i & 0x01) && !(i & (1 << 16)));
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}
