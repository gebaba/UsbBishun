/**
 * trie 树字库
 * 
 * 
 */
#include "trie_storage.h"
#include "storage.h"
#include "missing.h"

/**
 * 获取 trie 树的节点
 * 
 * state: 状态
 * 
 * return: 对应状态下的节点
 * 
 */
struct TrieNode getTrieNode(int state) {
    struct TrieNode trieNode;
    receiveData((char *) &trieNode, sizeof(struct TrieNode) - 3, sizeof(int) + state * (sizeof(struct TrieNode) - 3));
    return trieNode;
}

/**
 * 获取节点数据
 * 
 * trieNode: 节点
 * i: 节点数据 index 位置
 * data: 数据缓存
 * 
 * 
 */
void getData(struct TrieNode trieNode, int i, struct Data *data) {
    int j;
    int offset;
    receiveData((char *) &offset, sizeof(int), 0);
    for (j = 0; j <= i; j++) {
        int len;
        int lenWubi;
        char *wubi;
        receiveData((char *) data, sizeof(struct Data), offset + trieNode.offset);
        len = strlen(data->pinyin);
        lenWubi = strlen(wubi = &data->pinyin[len + 1]);
        memcpy(data->wubi, wubi, lenWubi + 1);
        offset += len + lenWubi + 36;
    }
}
