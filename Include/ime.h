/**
 * 双数组 trie 树笔画查询 
 * 
 * 
 */
#ifndef _IME_H_
#define _IME_H_

#define BITMAP_MAX   32
#define WUBI_MAX     10
#define PINYIN_MAX   20
#define BH_MAX       64

/**
 * 五笔和拼音数据有多个使用“|”分割
 *  
 * 
 */
struct Data {
    unsigned short charCode;
    char bitmap[BITMAP_MAX];
    char pinyin[PINYIN_MAX];
    char wubi[WUBI_MAX];
};

/**
 *  创建笔画查询
 * 
 *  bihua: 笔画1、2、3、4、5对应横竖撇捺折
 * 
 *  return: 查询句柄
 * 
 */
void *createSearch(char *bihua);

/**
 * 查询
 * 
 * handle: 查询句柄
 * data: 返回的查询数据
 * 
 * return: 结果
 * 
 */
int search(void *handle, struct Data *data);

/**
 * 关闭查询
 *  
 * handle: 查询句柄
 * 
 */
void freeSearch(void *handle);

#endif
