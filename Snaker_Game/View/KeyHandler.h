/******************************************************
    > File Name: KeyHandler.c
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/29.
    > Functional： Key Handler declaration
*******************************************************/

#ifndef RERTO_SNAKER_KEYHANDLER_H
#define RERTO_SNAKER_KEYHANDLER_H

#include "../Common/WinApiHelper.h"
/**
 * 定义结构处理默认方向键
 */
typedef  struct  _default_key_Handler{
    void* (*up)(char);
    void* (*down)(char);
    void* (*left)(char);
    void* (*right)(char);
}DefaultHandler;

/**
 * Special mapping
 */
typedef struct _key_mapping{
    char key;
    void* (*key_handler)(void*);
}KeyMapping;

/**
 * Key processing function of external call
 * @param handler
 * @param mapping
 * @param len
 */
void Key_Handler_Operator(DefaultHandler* handler,KeyMapping* mappings,int len);
#endif //RERTO_SNAKER_KEYHANDLER_H
