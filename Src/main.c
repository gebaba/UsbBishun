/**
 * MVC 
 * stm32f103c8t6 对应 STM32F10X_MD
 * 
 * 
 */
#include "display.h"
#include "graph.h"
#include "ime.h"
#include "storage.h"
#include "keyboard.h"
#include "usb_keyboard.h"

#include "missing.h"

#include "stm32f10x_conf.h"

#define CANDIDATE_MAX 64

const char *ALPHABET[] = {
    "\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x80\x00\x00\x00", //一
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", //丨
    "\x00\x00\x00\x00\x00\x80\x00\x40\x00\x20\x00\x18\x00\x06\xff\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", //丿
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x40\x00\x80\x00\x00\x01\x00\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", //丶
    "\x00\x00\x02\x00\x02\x38\x02\x46\x02\x41\x82\x40\x42\x40\x22\x40\x12\x40\x0a\x40\x06\x40\x02\x40\x00\x40\x00\x78\x00\x00\x00\x00", //乙
    "\xff\xff\x01\x80\x21\x82\x21\xa2\xfd\xbf\x21\x81\x01\x82\x25\xa2\xe9\x9f\x21\x82\x21\x82\xe9\xbf\x25\x82\x01\x80\x01\x80\xff\xff", //拼
    "\xff\xff\x01\x80\x09\xa0\x89\xa0\x89\xb8\x89\xa7\xf9\xa0\x89\xa0\x89\xa0\x89\xa0\x89\xbf\x09\xa0\x01\xa0\x01\x80\x01\x80\xff\xff", //五
    "\x00\x00\x00\x08\x80\x0f\x70\x02\xc0\x03\x00\x0e\x00\x08\x00\x00", // a
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\x90\x08\x60\x07\x00\x00\x00\x00", // b
    "\x00\x00\xe0\x07\x10\x08\x10\x08\x10\x08\x30\x04\x00\x00\x00\x00", // c
    "\x00\x00\x10\x08\xf0\x0f\x10\x08\x10\x08\xe0\x07\x00\x00\x00\x00", // d
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\xd0\x09\x30\x0c\x00\x00\x00\x00", // e
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\xd0\x01\x30\x00\x00\x00\x00\x00", // f
    "\x00\x00\xc0\x03\x20\x04\x10\x08\x10\x09\x30\x07\x00\x01\x00\x00", // g
    "\x00\x00\x10\x08\xf0\x0f\x80\x00\x80\x00\xf0\x0f\x10\x08\x00\x00", // h
    "\x00\x00\x10\x08\x10\x08\xf0\x0f\x10\x08\x10\x08\x00\x00\x00\x00", // i
    "\x00\x00\x00\x30\x10\x20\x10\x20\xf0\x1f\x10\x00\x10\x00\x00\x00", // j
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\x40\x01\x30\x0e\x10\x08\x00\x00", // k
    "\x00\x00\x10\x08\xf0\x0f\x10\x08\x00\x08\x00\x08\x00\x0c\x00\x00", // l
    "\x10\x08\xf0\x0f\xf0\x00\x00\x0f\xf0\x00\xf0\x0f\x10\x08\x00\x00", // m
    "\x00\x00\x10\x08\xf0\x0f\xc0\x08\x10\x03\xf0\x0f\x10\x00\x00\x00", // n
    "\x00\x00\xe0\x07\x10\x08\x10\x08\x10\x08\xe0\x07\x00\x00\x00\x00", // o
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\x90\x00\x60\x00\x00\x00\x00\x00", // p
    "\x00\x00\xe0\x07\x10\x0a\x10\x0a\x10\x1c\xe0\x17\x00\x00\x00\x00", // q
    "\x00\x00\x10\x08\xf0\x0f\x90\x08\x90\x01\x60\x0e\x00\x08\x00\x00", // r
    "\x00\x00\x60\x0c\x90\x08\x90\x08\x10\x09\x30\x06\x00\x00\x00\x00", // s
    "\x00\x00\x30\x00\x10\x08\xf0\x0f\x10\x08\x30\x00\x00\x00\x00\x00", // t
    "\x00\x00\x10\x00\xf0\x07\x00\x08\x00\x08\xf0\x07\x10\x00\x00\x00", // u
    "\x00\x00\x10\x00\xf0\x01\x00\x0e\x80\x03\x70\x00\x10\x00\x00\x00", // v
    "\x00\x00\xf0\x00\x00\x0f\xf0\x01\x00\x0f\xf0\x00\x00\x00\x00\x00", // w
    "\x00\x00\x10\x08\x70\x0e\x80\x01\x70\x0e\x10\x08\x00\x00\x00\x00", // x
    "\x00\x00\x10\x00\xf0\x08\x00\x0f\xf0\x08\x10\x00\x00\x00\x00\x00", // y
    "\x00\x00\x30\x08\x10\x0e\x90\x09\x70\x08\x10\x0c\x00\x00\x00\x00"  // z
};

char mode;
char input[BH_MAX + 1];

void *handle;
struct Data candidate[CANDIDATE_MAX];
int candidateSize;
int start;
int current;

char bitmap[ROW_MAX * COL_MAX];

/**
 * 显示视图
 * 
 *  字
 * [拼] zi
 *  丶丶乙乙丨一
 * [字]寐寎寤賔寣寢寱
 * 
 * 
 */
void renderView(void) {
    static struct MonoData d = {ROW_MAX * 8, COL_MAX, bitmap};
    struct MonoData monoData = {16};
    int i;
    int j;
    int len;
    char *ptr;
    /**
     * 清屏
     * 
     * 
     */
    i = sizeof(bitmap);
    while (i--) {
        bitmap[i] = 0;
    }
    if (candidateSize) {
        monoData.h = 16;
        monoData.bitmap = candidate[current].bitmap;
        copyImage(&d, 0, 0, monoData, 0);
        monoData.bitmap = (char *) ALPHABET[!mode ? 5 : 6];
        copyImage(&d, 16, 0, monoData, 0);
        ptr = !mode ? candidate[current].pinyin : candidate[current].wubi;
        monoData.h = 8;
        for (int i = 0; i < strlen(ptr); i++) {
            if ('a' <= ptr[i] && ptr[i] <= 'z') {
                monoData.bitmap = (char *) ALPHABET[7 + ptr[i] - 'a'];
                copyImage(&d, 16, 16 + i * 8, monoData, 0);
            }
        }
    }
    monoData.h = 16;
    for (i = 0, j = (len = strlen(input)) > 8 ? len - 8 : 0; j < len; i++, j++) {
        monoData.bitmap = (char *) ALPHABET[input[j] - 1];
        copyImage(&d, 32, i * 16, monoData, 0);
    }
    for (i = 0, j = start; i < 8 && j < candidateSize; i++, j++) {
        monoData.bitmap = candidate[j].bitmap;
        copyImage(&d, 48, i * 16, monoData, j == current);
    }
}

/**
 * 重新搜索
 * 
 * 
 */
void onInputChange(void) {
    int i;
    if (handle) {
        freeSearch(handle);
    }
    if (strlen(input) && (handle = createSearch(input))) {
        for (i = 0; i < 8; i++) {
            if (!search(handle, &candidate[i])) {
                break;
            }
        }
        candidateSize = i;
    } else {
        candidateSize = 0;
    }
    start = 0;
    current = 0;
}

/**
 * 执行按键动作
 * 
 * key: 按键 
 * 
 * 
 */
void doKey(char key) {
    switch (key) {
    case KEY_H:
    case KEY_S:
    case KEY_P:
    case KEY_N:
    case KEY_Z:
        {
            int len = strlen(input);
            if (len < BH_MAX) {
                input[len++] = key + 1, input[len] = 0;
                onInputChange();
            }
        }
        break;
    case KEY_OK:
        if (current < candidateSize) {
            int i;
            char *key = !mode ? candidate[current].pinyin : candidate[current].wubi;
            for (i = 0; i < strlen(key) && key[i] != '|'; i++) {
                sendKey(key[i]);
            }
            input[0] = 0;
            onInputChange();
        }
        break;
    case KEY_MODE:
        mode = !mode;
        break;
    case KEY_DELETE:
        {
            int len = strlen(input);
            if (len) {
                input[--len] = 0;
                onInputChange();
            }
        }
        break;
    case KEY_CLEAR:
        /**
         * 清除
         * 
         * 
         */
        input[0] = 0;
        onInputChange();
        break;
    case KEY_PREVIOUS:
        if (current) {
            current--;
            if (start > current) {
                start--;
            }
        }
        break;
    case KEY_NEXT:
        if (current < candidateSize && candidateSize < CANDIDATE_MAX) {
            current++;
            if (current == candidateSize) {
                if (search(handle, &candidate[current])) {
                    candidateSize++;
                } else {
                    current--;
                }
            }
            if (start + 8 <= current) {
                start++;
            }
        }
        break;
    case KEY_ZOOM:
        sendKey('+');
        break;
    case KEY_ZOOMOUT:
        sendKey('-');
        break;
    }
}

#ifdef INITIALIZE_STORAGE

#define PAGESIZE 256
#define SECTORSIZE 4096
#define BAUD 115200

/**
 * 通过串口数据初始化存储器
 * 
 * 
 */
int main(int argc, char *argv[]) {
    char buf[SECTORSIZE];
    int start = 0;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    {
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    {
        USART_InitTypeDef USART_InitStruct;
        USART_InitStruct.USART_BaudRate = BAUD;
        USART_InitStruct.USART_WordLength = USART_WordLength_8b;
        USART_InitStruct.USART_StopBits = USART_StopBits_1;
        USART_InitStruct.USART_Parity = USART_Parity_No ;
        USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStruct);
    }
    USART_Cmd(USART1, ENABLE);
    initializeSpi();
    while (1) {
        int i;
        for (i = 0; i < SECTORSIZE;) {
            if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
                buf[i++] = USART_ReceiveData(USART1);
            }
        }
        erase(start);
        for (i = 0; i < SECTORSIZE; i += PAGESIZE) {
            sendData(&buf[i], PAGESIZE, start + i);
        }
        start += SECTORSIZE;
        USART_SendData(USART1, 0xff);
    } 
    return 0;
}

#else
/**
 * 主程序
 * 
 * 
 */
int main(int argc, char *argv[]) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    initializeSpi();
    initializeLcd();
    initializeKey();
    // initializeUsb();
    while (1) {
        doKey(readKey());
        renderView();
        draw(bitmap);
    }
}

#endif