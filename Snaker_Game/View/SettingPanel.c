/******************************************************
    > File Name: SettingPanel.c
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent·Vic  on 2018/3/31.
    > Functional： Setting Panel implementation
*******************************************************/

#include "SettingPanel.h"

Panel* Setting_Panel=NULL;
//Withdrawal judgment
_Bool SetExit=0;

/**
 * Setting panel information and options
 */
TextView Setting_Panel_Views[]= {
        {5,3, 0xE,0x0,28,"Return change state!!!", 0},
        {5,5, 0x0,0xE,28,"Background music (on/off):ON", 1},
        {5,7, 0xE,0x0,28,"Sound effects (on/off):ON", 1},
        {5,9, 0xE,0x0,28,"Eatting effects (on/off):OFF", 1}
};
/**
 * Game initialization information
 */
Setting* setting_data=NULL;

/**
 * Setting the panel initialization function
 */
void Setting_Initial();

/**
 * Exiting
 * @param v
 * @return void*
 */
void* Setting_Escape_Key_Press(char v);

/**
 * Return key processing event
 * @param v
 * @return void*
 */
void* Setting_Enter_Key_Press(char v);

/**
 * Change the background music state
 */
void Change_background_music_state();

/**
 * Backdrop music switch
 */
void Change_sound_state();

/**
 * Change the sound switch for food
 */
void Change_Eatting_effects_state();

void Setting_Panel_Init()
{
    if(Setting_Panel==NULL){
        Setting_Panel=PanelInit();
    }
    Setting_Initial();
    Setting_Panel->x=22;
    Setting_Panel->y=1;
    Setting_Panel->Width=56;
    Setting_Panel->Heigth=22;
    Setting_Panel->color=0xF;
    Setting_Panel->bgcolor=0x0;
}

void Setting_Initial()
{
    srand(time(NULL));
    if(NULL == setting_data){
        setting_data=(Setting*)malloc(sizeof(Setting));
        memset(setting_data,0, sizeof(Setting));
        setting_data->Map_Width=26;
        setting_data->Map_Height=20;
        setting_data->snake_x=2;
        setting_data->snake_y=11;
        setting_data->shake_color=rand()%0xF;
        setting_data->snake_speed=0.3;
        setting_data->snake_length=3;
        setting_data->Sound_effects=1;
        setting_data->Eat_effects=0;
        setting_data->Background_music=1;
        setting_data->direction=S_RIGHT;
    }
}

void* Setting_Panel_Up_Handler(char v)
{
    int len = sizeof(Setting_Panel_Views) / sizeof(TextView);
    ChangeSelectedView(Setting_Panel_Views,len,Setting_Panel->bgcolor,Setting_Panel->color,0);
    drawView(Setting_Panel,Setting_Panel_Views,len);
}

void* Setting_Panel_Down_Handler(char v)
{
    int len = sizeof(Setting_Panel_Views) / sizeof(TextView);
    ChangeSelectedView(Setting_Panel_Views,len,Setting_Panel->bgcolor,Setting_Panel->color,1);
    drawView(Setting_Panel,Setting_Panel_Views,len);
}

void drawSettingPanel()
{
    Setting_Panel_Init();
    if(NULL!=Setting_Panel){
        drawPanel(Setting_Panel);
        int len = sizeof(Setting_Panel_Views)/sizeof(TextView);
        drawView(Setting_Panel,Setting_Panel_Views,len);
    }

}

void Setting_Panel_Key_Bind()
{
    DefaultHandler handler={Setting_Panel_Up_Handler,Setting_Panel_Down_Handler};
    KeyMapping mappings[]={
            {13,Setting_Enter_Key_Press},
            {27,Setting_Escape_Key_Press}
    };
    int len= sizeof(mappings)/ sizeof(KeyMapping);
    Key_Handler_Operator(&handler,mappings,len);
}

Setting *GetSettingData()
{
    if(NULL==setting_data){
        Setting_Initial();
    }
    return setting_data;
}

void* Setting_Enter_Key_Press(char v)
{
    int len = sizeof(Setting_Panel_Views) / sizeof(TextView);
    int QueryIndex = QuerySelectView(Setting_Panel_Views,len,Setting_Panel->bgcolor);
    if(QueryIndex==1){
        Change_background_music_state();
    }
    if(QueryIndex==2){
        Change_sound_state();
    }
    if(QueryIndex==3){
        Change_Eatting_effects_state();
    }
}

void* Setting_Escape_Key_Press(char v)
{
    SetExit=1;
}

void Change_background_music_state()
{
    if(setting_data->Background_music==1){
        strcpy(Setting_Panel_Views[1].txt,"Background music (on/off):OFF");
    }else{
        strcpy(Setting_Panel_Views[1].txt,"Background music (on/off):ON");
    }
    setting_data->Background_music^=1;
    drawSettingPanel();
}

void Change_sound_state()
{

    if(setting_data->Sound_effects==1){
        strcpy(Setting_Panel_Views[2].txt,"Sound effects (on/off):OFF");
    }else{
        strcpy(Setting_Panel_Views[2].txt,"Sound effects (on/off):ON");
    }
    setting_data->Sound_effects^=1;
    drawSettingPanel();
}

void Change_Eatting_effects_state()
{
    if(setting_data->Eat_effects==1){
        strcpy(Setting_Panel_Views[3].txt,"Eatting effects (on/off):OFF");
    }else {
        strcpy(Setting_Panel_Views[3].txt,"Eatting effects (on/off):ON");
    }
    setting_data->Eat_effects^=1;
    drawSettingPanel();
}

_Bool getSettingExit()
{
    return SetExit;
}

void InitialSettingControlInfo()
{
    SetExit=0;
}
