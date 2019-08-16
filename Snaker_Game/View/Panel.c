/******************************************************
    > File Name: Panel.c
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/27.
    > Functional： Base Panel implementation
*******************************************************/

#include "Panel.h"

Panel *PanelInit()
{
    Panel* panel=(Panel*)malloc(sizeof(Panel)); //malloc Panel
    memset(panel,0, sizeof(Panel)); //Collate memory
    /**
     * Panel initialization information
     */
    panel->Width=5;
    panel->Heigth=5;
    panel->HLetter='-';
    panel->VLetter='|';
    panel->color=0xf;
    panel->bgcolor=0x0;
    return panel;
}

void drawPanel(Panel *panel)
{
    /**
     * Background drawing
     */
    fillText(panel->x,panel->y,panel->bgcolor<<4|panel->color,' ',panel->Width,panel->Heigth);
    /**
     * Line drawing
     */
    drawVline(panel->x,panel->y,panel->bgcolor<<4|panel->color,panel->VLetter,panel->Heigth);
    drawVline(panel->x+panel->Width-1,panel->y,panel->bgcolor<<4|panel->color,panel->VLetter,panel->Heigth);
    /**
     * Cross line drawing
     */
    drawHline(panel->x,panel->y,panel->bgcolor<<4|panel->color,panel->HLetter,panel->Width);
    drawHline(panel->x,panel->y+panel->Heigth,panel->bgcolor<<4|panel->color,panel->HLetter,panel->Width);
}

void drawView(Panel *panel, TextView *Views, int len)
{
    int i;
    for (int i = 0; i < len; i++)
    {
        //Get the pointer of the I display component
        TextView* v=Views+i;
        setCurrsorPosition(panel->x+v->x,panel->y+v->y);
        setColor(v->bgcolor<<4|v->color);
        PrintText(v->txt,v->size);
    }
}

int QuerySelectView(TextView *views, int len, int color)
{
    int i;
    for (i= 0; i <len ; ++i)
    {
        TextView* v=views+i;
        if(v->color==color)
        {
            return i;
        }
    }
    return -1;
}

void ChangeSelectedView(TextView *views, int len, int color, int bgcolor, _Bool UpOrDown)
{
    //The one that is currently selected is the one
    int SelectedIndex=QuerySelectView(views,len,color);
    SelectedIndex=SelectedIndex> -1 ? SelectedIndex:0;
    //Modify the color of the current selected component
    TextView* SelectedView=views+SelectedIndex;
    SelectedView->color=bgcolor;
    SelectedView->bgcolor=color;
    TextView* NextSelected=NULL;
    //Look up the next
    if(UpOrDown){
        int i;
        for(i=SelectedIndex+1;i<len+SelectedIndex;i++)
        {
            TextView* v=views+(i%len);
            if(v->selectAble){
                NextSelected=v;
                break;
            }
        }
    }else{
        int i;
        for(i=SelectedIndex+len-1;i>0;i--)
        {
            TextView* v=views+(i%len);
            if(v->selectAble){
                NextSelected=v;
                break;
            }
        }
    }
    //Change the color of the next selected component
    if(NextSelected!=NULL){
        TextView* SelectedView=views+SelectedIndex;
        SelectedView->color=bgcolor;
        SelectedView->bgcolor=color;
        NextSelected->color=color;
        NextSelected->bgcolor=bgcolor;
    }
}