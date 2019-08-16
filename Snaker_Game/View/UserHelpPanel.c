/******************************************************
    > File Name: UserHelpPanel.c
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent·Vic  on 2018/4/7.
    > Functional： User Help Panel implementation
*******************************************************/

#include "UserHelpPanel.h"

Panel* Help_Panel=NULL;

TextView Help_Panel_Views[]= {
        {3,2, 0xE,0x0,40,"Key and'w','s','A','D' selected function,Select", 0},
        {3,4, 0xE,0x0,50,"the game options and enter the game by return", 0},
        {3,6, 0xE,0x0,20,"Game rules:", 0},
        {3,8, 0xE,0x0,50,"    Every time you eat a piece of food,you get", 0},
        {3,10, 0xE,0x0,20," a body, plus 10 points, to a certain fraction,", 0},
        {3,12, 0xE,0x0,20," and speed up. Eat the end of your game.", 0},
        {3,14 ,0xE,0x0,40,"If you need to quit", 0},
        {3,16 ,0xE,0x0,40,"Press the ESC key or choose to exit the game", 0},
        {3,18 ,0xE,0x0,40,"Press the space to suspend the game!!", 0}
};

void Help_Panel_Init();

void Help_Panel_Init()
{
    if(Help_Panel==NULL){
        Help_Panel=PanelInit();
    }
    Help_Panel->x=22;
    Help_Panel->y=1;
    Help_Panel->Width=56;
    Help_Panel->Heigth=22;
    Help_Panel->color=0xF;
    Help_Panel->bgcolor=0x0;
}
void drawHelpPanel()
{
    Help_Panel_Init();
    if(NULL!=Help_Panel){
        drawPanel(Help_Panel);
        int len = sizeof(Help_Panel_Views)/sizeof(TextView);
        drawView(Help_Panel,Help_Panel_Views,len);
    }
}
