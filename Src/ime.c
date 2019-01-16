#include "ime.h"
#include "trie_storage.h"
#include "missing.h"

#define QUEUE_MAX 0x40

/**
 * 循环队列
 * 
 * 
 */
struct Queue {
    int data[QUEUE_MAX];
    int f;
    int r;
    int c;
};

/**
 * 记录了 trie 树的当前位置
 * 
 * 
 */
struct Context {
    int i;
    struct Queue queue;
};

static void push(struct Queue *queue, int data) {
    if (queue->c < QUEUE_MAX) {
        queue->c++;
        queue->data[queue->r] = data;
        queue->r = (queue->r + 1) % QUEUE_MAX;
    }
};

static void drop(struct Queue *queue) {
    if (queue->c) {
        queue->c--;
        queue->f = (queue->f + 1) % QUEUE_MAX;
    }
}

/**
 *  创建笔画查询
 * 
 *  bihua: 笔画1、2、3、4、5对应横竖撇捺折
 * 
 *  return: 查询句柄
 * 
 */
void *createSearch(char *bihua) {
    struct Context *context;
    int s = 0;
    int i;
    int t;
    struct TrieNode trieNode;
    context = (struct Context *) malloc(sizeof(struct Context));
    if (context) {
        for (i = 0; i < strlen(bihua); i++) {
            trieNode = getTrieNode(s);
            t = trieNode.b + bihua[i];
            trieNode = getTrieNode(t);
            if (trieNode.c != s) {
                free(context);
                return 0;
            }
            s = t;
        }
        context->i = 0;
        context->queue.f = context->queue.r = context->queue.c = 0;
        push(&context->queue, s);
    }
    return context;
}

/**
 * 查询
 * 
 * handle: 查询句柄
 * data: 返回的查询数据
 * 
 * return: 结果
 * 
 */
int search(void *handle, struct Data *data) {
    struct Context *context = (struct Context *) handle;
    struct TrieNode trieNode;
    int s;
    int b;
    int i;
    int t;
    while (context->queue.c) {
        s = context->queue.data[context->queue.f];
        trieNode = getTrieNode(s);
        if (context->i < trieNode.size) {
            getData(trieNode, context->i++, data);
            break;
        }
        drop(&context->queue);
        b = trieNode.b;
        context->i = 0;
        for (i = 1; i <= 5; i++) {
            t = b + i;
            trieNode = getTrieNode(t);
            if (trieNode.c == s) {
                push(&context->queue, t);
            }
        }
    }
    return !!context->queue.c;
}

/**
 * 关闭查询
 *  
 * handle: 查询句柄
 * 
 */
void freeSearch(void *handle) {
    free(handle);
}
