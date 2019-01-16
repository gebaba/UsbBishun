#include "graph.h"

/**
 * 拷贝图像
 * 
 * dest: 目标位置
 * x: 横坐标
 * y: 纵坐标
 * data: 源图像
 * 
 */
void copyImage(struct MonoData *dest, int x, int y, struct MonoData data, int rop) {
    int i;
    int j;
    int t;
    int r;
    /**
     * 没有考虑到超出的情况
     * 
     * 
     */
    for (i = 0; i < data.h; i++) {
        for (j = 0; j < data.w; j++) {
            t = dest->bitmap[((y + i) * dest->w + x + j) / 8];
            r = 1 << ((x + j) % 8);
            t &= ~r;
            if (data.bitmap[(i * data.w + j) / 8] & (1 << (j % 8))) {
                if (!rop) {
                    t |= r;
                }
            } else if (rop) {
                t |= r;
            }
            dest->bitmap[((y + i) * dest->w + x + j) / 8] = t;
        }
    }
}