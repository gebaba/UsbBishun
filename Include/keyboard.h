/**
 * 扫描按键
 * 
 */
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define KEY_H         0
#define KEY_S         1
#define KEY_P         2
#define KEY_N         3
#define KEY_Z         4
#define KEY_MODE      5
#define KEY_OK        6
#define KEY_PREVIOUS  7
#define KEY_NEXT      8
#define KEY_DELETE    9
#define KEY_ZOOM      10
#define KEY_ZOOMOUT   11
#define KEY_CLEAR     12

/**
 * 读取按键（阻塞）
 *  
 * return: 按键值
 * 
 */
int readKey(void);

/**
 * 初始化 
 * 
 */
void initializeKey(void);

#endif
