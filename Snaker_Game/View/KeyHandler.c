/******************************************************
    > File Name: KeyHandler.h
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/29.
    > Functional： Key Handler implementation
*******************************************************/

#include "KeyHandler.h"

void Key_Handler_Operator(DefaultHandler *handler, KeyMapping *mappings, int len)
{
    char recivekey=0;
    recivekey=ReadChar();
    if(recivekey!=0){
        if(recivekey==0xffffffe0) {
            recivekey=ReadChar();
        }
        /**
         * Conventional key processing
         */
        if(handler!=NULL)
        {
                switch (recivekey)
                {
                case 'w':   //0x48
                case 0x48:
                    if(handler->up!=NULL)
                    {
                        handler->up('w');
                    }
                    break;
                case 's':   //0x50
                case 0x50:
                    if(handler->down!=NULL)
                    {
                        handler->down('s');
                    }
                    break;
                case 'a':   //0x4b
                case 0x4b:
                    if(handler->left!=NULL)
                    {
                        handler->left('a');
                    }
                    break;  //0x4d
                case 'd':
                case 0x4d:
                    if(handler->right!=NULL)
                    {
                        handler->right('d');
                    }
                    break;
            }
        }
        /**
         * Special mapping processing
         */
        if(NULL!=mappings&&len>0)
        {
            int i;
            for(i=0;i<len;i++)
            {
                KeyMapping* mapping=mappings+i;
                if(mapping->key==recivekey)
                {
                    if(mapping->key_handler!=NULL)
                    {
                        mapping->key_handler(recivekey);
                    }
                }
            }
        }
    }
}
