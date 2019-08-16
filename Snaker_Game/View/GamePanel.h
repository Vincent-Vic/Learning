

/******************************************************
    > File Name: GamePanel.h
    > Author: Vincent¡¤Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent¡¤Vic  on 2018/4/1.
    > Functional£º Game Panel declaration
*******************************************************/

#ifndef RERTO_SNAKER_GAMEPANEL_H
#define RERTO_SNAKER_GAMEPANEL_H

#include "Panel.h"
#include "../Model/GameData.h"

/**
 * Draw the game panel
 */
void drawGamePanel();

/**
 * Game panel keyboard event processing
 */
void GamePanelKeyHandler();

/**
 *Get the game out of the game
 * 1 Exit
 * 0 Do not quit
 * @return _Bool
 */
_Bool getGameExit();

/**
 * Get to pause the game
 * 1 Pause
 * 0 Continue
 * @return
 */
_Bool getGameSuspend();

/**
 * Initializing game control information
 * @param E
 * @param S
 */
void InitialGameControlInfo();
#endif //RERTO_SNAKER_GAMEPANEL_H
