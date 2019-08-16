/******************************************************
    > File Name: Panel.h
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/27.
    > Functional： Base Panel declaration
*******************************************************/

#ifndef RERTO_SNAKER_PANEL_H
#define RERTO_SNAKER_PANEL_H


#include "../Common/WinApiHelper.h"
#include "KeyHandler.h"

/**
 * Base Panel Struct
 */
typedef struct _base_panel{
    int x;
    int y;
    int Width;
    int Heigth;
    char HLetter;
    char VLetter;
    int color;
    int bgcolor;
}Panel;

/**
 * Base display components
 */
typedef  struct  _base_text_view{
    int x;
    int y;
    int color;
    int bgcolor;
    int size;
    char txt[50];
    _Bool  selectAble;  //Whether it can be selected (0 can not be selected (default), and 1 can be selected).
}TextView;

/**
 * Panel initialization function
 * @return
 */
Panel* PanelInit();

/**
 * Panel drawing function
 * @param panel  Panels that need to be drawn
 */
void drawPanel(Panel* panel);

/**
 * Display component drawing functions
 * @param panel
 * @param Views
 * @param len
 */
void drawView(Panel* panel,TextView* Views, int len);

/**
 * Query which component is selected
 * @param views
 * @param len
 * @param color
 * @return int
 */
int QuerySelectView(TextView* views,int len,int color);

/**
 * Select component switch function, select the back panel and reverse the background.
 * @param views
 * @param len
 * @param color
 * @param bgcolor
 * @param UpOrDown
 */
void ChangeSelectedView(TextView* views,int len,int color,int bgcolor, _Bool UpOrDown);

#endif //RERTO_SHAKER_PANEL_H