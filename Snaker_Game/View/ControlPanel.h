/******************************************************
    > File Name: ControlPanel
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/27.
    > Functional： Control Panel declaration
*******************************************************/

#ifndef RERTO_SNAKER_CONTROLPANEL_H
#define RERTO_SNAKER_CONTROLPANEL_H

#include "Panel.h"
#include "SettingPanel.h"
/**
 * 定义外部预置处理
 */
typedef  struct _control_panel_operator{
    //User Help Panel
    void (*view_help_panel)();
    //Game Panel
    void (*view_game_pancel)();
    //Setting Panel
    void (*view_setting_panel)();
    //Exit Panel
    void (*view_exit_panel)();
    //Start Game
    void (*start_game)();
    //Change score
    void (*change_score)();
    //Change Len
    void (*change_len)();
    //Change Speed
    void (*change_speed)();
}ControlPanelOperator;
/**
 * Contro Panel Realization
 */
void drawControlPanel();

void Control_Panel_Key_Bind();

/**
 * 控制面板处理函数
 * @param anOperator
 */
void setControlPanelOperator(ControlPanelOperator* anOperator);

/**
 * Set the snake control panel information
 * @param score
 * @param length
 * @param speed
 */
void setGameInfo(int score,int length,double speed);
#endif //RERTO_SNAKER_CONTROLPANEL_H
