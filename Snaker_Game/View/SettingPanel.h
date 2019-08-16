/******************************************************
    > File Name: SettingPanel.h
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent·Vic  on 2018/3/31.
    > Functional： Setting Panel declaration
*******************************************************/

#ifndef RERTO_SNAKER_SETTINGPANEL_H
#define RERTO_SNAKER_SETTINGPANEL_H

#include "Panel.h"
#include "../Model/GameData.h"

/**
 * Setting up basic information
 */
typedef struct _setting_data{
    int snake_x;
    int snake_y;
    int snake_length;
    int shake_color;
    double snake_speed;
    int Map_Width;
    int Map_Height;
    int Sound_effects;
    int Eat_effects;
    int Background_music;
    SnakeDirection direction;
}Setting;

/**
 * External acquisition of data
 * @return Setting
 */
Setting* GetSettingData();

/**
 * Draw the settings panel
 */
void drawSettingPanel();

void Setting_Panel_Key_Bind();

/**
 *Get the game out of the game
 * 1 Exit
 * 0 Do not quit
 * @return _Bool
 */
_Bool getSettingExit();

/**
 * Initializing Setting control information
 * @param E
 * @param S
 */
void InitialSettingControlInfo();
#endif //RERTO_SNAKER_SETTINGPANEL_H
