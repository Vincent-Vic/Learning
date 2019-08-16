/******************************************************
    > File Name: GamePanel.h
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent Vic  on 2018/4/1.
    > Functional?? Game Panel implementation
*******************************************************/

#include "GamePanel.h"
/**
 * Global game panel
 */
Panel* game_panel=NULL;

//Withdrawal judgment
_Bool Exit=0;
//Pause and continue state lock
_Bool Suspend=0;

/**
 * Invoking an external member
 */
extern GameData* gameData;

/**
 * Game panel initialization
 * @return Panel
 */
Panel* initial_game_panel();

/**
 * Game panel rendering
 */
void drawGamePanel();

/**
 * Game data rendering
 */
void drawGameData();

/**
 * Upper key processing
 * @param key
 * @return
 */
void* _game_panel_up(char key);

/**
 * Lower direction key processing
 * @param key
 * @return
 */
void* _game_panel_down(char key);

/**
 * Left direction key processing
 * @param key
 * @return
 */
void* _game_panel_left(char key);

/**
 * Right direction key processing
 * @param key
 * @return
 */
void* _game_panel_right(char key);

/**
 * Exiting operation
 * @param v
 * @return void*
 */
void* Escape_Key_Press(char v);

/**
 * Pause operation
 * @param v
 * @return
 */
void* Game_Suspend_Key_Press(char v);
/*-----------------------------------------------------------------------------------------------------------------*/
void* Game_Escape_Key_Press(char v)
{
    Exit=1;
}

void* Game_Suspend_Key_Press(char v)
{
    Suspend ^=1;
}

void GamePanelKeyHandler()
{
    DefaultHandler Handler={_game_panel_up,_game_panel_down,_game_panel_left,_game_panel_right};
    KeyMapping mappings[]={
            {32,Game_Suspend_Key_Press},
            {27,Game_Escape_Key_Press}
    };
    int len= sizeof(mappings)/ sizeof(KeyMapping);
    Key_Handler_Operator(&Handler,mappings,len);
}

Panel* initial_game_panel()
{
    if(game_panel==NULL){
        game_panel=PanelInit();
    }
    game_panel->x=22;
    game_panel->y=1;
    game_panel->Width=56;
    game_panel->Heigth=22;
    game_panel->color=0x0;
    game_panel->bgcolor=0xF;
}

void drawGamePanel()
{
    initial_game_panel();
    if(NULL!=game_panel){
        drawPanel(game_panel);
        if(NULL!=gameData){
            drawGameData();
        }

    }
}

_Bool getGameExit()
{
    return Exit;
}

_Bool getGameSuspend()
{
    return Suspend;
}

void InitialGameControlInfo()
{
    Exit=0;
    Suspend=0;
}

void drawGameData()
{
    //Food drawing
    int food_x=game_panel->x+gameData->food->x*2+1;   //Panel x coordinates + food data x coordinates * 2
    int food_y=game_panel->y+gameData->food->y+1;
    setCurrsorPosition(food_x,food_y);
    setColor(game_panel->bgcolor << 4|gameData->food->Color);
    PrintText("¡ñ",2);
    //Snake body drawing
    SnakeNode* loop;
    for(loop=gameData->snake;loop!=NULL;loop=loop->next)
    {
        int node_x=game_panel->x+loop->x*2+1;
        int node_y=game_panel->y+loop->y+1;
        setCurrsorPosition(node_x,node_y);
        setColor(game_panel->bgcolor << 4|loop->Color);
        PrintText("¡ö",2);
    }
}

void* _game_panel_up(char key)
{
    if(gameData->direction!=S_DOWN){
        gameData->direction=S_UP;
    }
}

void *_game_panel_down(char key)
{
    if(gameData->direction!=S_UP){
        gameData->direction = S_DOWN;
    }
}

void* _game_panel_left(char key)
{
    if(gameData->direction!=S_RIGHT){
        gameData->direction = S_LEFT;
    }
}

void* _game_panel_right(char key)
{
    if(gameData->direction!=S_LEFT){
        gameData->direction = S_RIGHT;
    }
}
