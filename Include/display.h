/**
 * LCD12864 显示驱动 ST7567
 * 
 */
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#define ROW_MAX  9
#define COL_MAX  132

/**
 * 屏幕初始化
 * 
 * 
 */
void initializeLcd(void);

/**
 * 显示图像
 * 
 * data: 整屏数据
 * 
 */
void draw(char *data);

#endif
