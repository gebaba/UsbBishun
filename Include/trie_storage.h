/**
 * trie 树字库
 * 
 */
#ifndef _TRIESTORAGE_H_
#define _TRIESTORAGE_H_

#include "ime.h"

struct TrieNode {
    int b;
    int c;
    int offset;
    unsigned char size;
};

/**
 * 获取 trie 树的节点
 * 
 * state: 状态
 * 
 * return: 对应状态下的节点
 * 
 */
struct TrieNode getTrieNode(int state);

/**
 * 获取节点数据
 * 
 * trieNode: 节点
 * i: 节点数据 index 位置
 * data: 数据缓存
 * 
 * 
 */
void getData(struct TrieNode trieNode, int i, struct Data *data);

#endif
