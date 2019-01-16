#ifndef _GRAPH_H_
#define _GRAPH_H_

struct MonoData {
    int w;
    int h;
    char *bitmap;
};

/**
 * 拷贝图像
 * 
 * dest: 目标位置
 * x: 横坐标
 * y: 纵坐标
 * data: 源图像
 * rop: 光栅操作 0-正常 1-取反
 * 
 */
void copyImage(struct MonoData *dest, int x, int y, struct MonoData data, int rop);

#endif
