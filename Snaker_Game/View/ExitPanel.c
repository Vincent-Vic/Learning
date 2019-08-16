/******************************************************
    > File Name: ExitPanel.c
    > Author: Vincent¡¤Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent¡¤Vic  on 2018/4/7.
    > Functional£º Exit Panel implementation
*******************************************************/

#include "ExitPanel.h"

Panel* Exit_Panel=NULL;

TextView Exit_Panel_Views[]= {
        {5,3, 0xE,0x0,28,"Do you end the game:", 0},
        {5,5, 0xE,0x0,28,"Confirmation please press return", 0},
};
/**
 * Exit panel initialization
 */
void Exit_Panel_Init();

void Exit_Panel_Init()
{
    if(Exit_Panel==NULL){
        Exit_Panel=PanelInit();
    }
    Exit_Panel->x=22;
    Exit_Panel->y=1;
    Exit_Panel->Width=56;
    Exit_Panel->Heigth=22;
    Exit_Panel->color=0xF;
    Exit_Panel->bgcolor=0x0;
}

void drawExitPanel() {
    Exit_Panel_Init();
    if(NULL!=Exit_Panel) {
        drawPanel(Exit_Panel);
        int len = sizeof(Exit_Panel_Views) / sizeof(TextView);
        drawView(Exit_Panel, Exit_Panel_Views, len);
    }
}
