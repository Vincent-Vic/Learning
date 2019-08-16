/******************************************************
    > File Name: GameControl.c
    > Author: Vincent Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent Vic  on 2018/4/6.
    > Functional  Game Control implementation
*******************************************************/
#include "GameControl.h"

/**
 * Game data global variable
 */
GameData* gameData=NULL;

/**
 * Basic Setting
 */
void Basic_setup();

/**
 * Start Game
 */
void StartGame();

/**
 * Snake initialization
 */
void SnakeInitial(Setting* setting);

/**
 * Game initialization
 */
void GameInitial();

/**
 * Fresh food information
 */
void FreshFoodInfo();

/**
 * Ready Game Main
 */
void ReadyGame();

/**
 * Snake Move Function
 */
void SnakeMove();

/**
 * Snake predation Function
 */
void EatFood();

/**
 * Sound effects when eating food
 */
void EatEffects();

/**
 * Determine position by direction
 * @param x
 * @param y
 */
void PositionByDirection(int *x, int *y);

/**
 * Judge death
 * @return
 */
_Bool CheckDead();

/**
 * Print death message
 */
void PrintDeadInfo();

/**
 * Exit key operation
 * @param v
 * @return
 */
void* Escape_Key_Press(char v);

/**
 * Background music function
 */
void Background_Music();

/**
 * Death music
 */
void DeadMusic();

void PrintDeadInfo()
{
    setCurrsorPosition(28,6);
    setColor(0x4f);
    PrintText("Unfortunately, you have killed yourself!!",44);
    char score_str [50];
    sprintf(score_str,"Final Score :%d",gameData->score);
    setCurrsorPosition(28,8);
    setColor(0x4f);
    PrintText(score_str,18);
    char len_str[50];
    sprintf(len_str,"Final length:%d",gameData->length);
    setCurrsorPosition(28,10);
    setColor(0x4f);
    PrintText(len_str,16);
    char speed_str[50];
    sprintf(speed_str,"The fastest S / G :%.2lf",gameData->speed);
    setCurrsorPosition(28,12);
    setColor(0x4f);
    PrintText(speed_str,22);
    drawControlPanel();
    DeadMusic();
}

void DeadMusic()
{
    Setting *setting = GetSettingData();
    //If the sound is open, perform the operation
    if(setting->Sound_effects==1){
      if(gameData->score > 600){
          PlayGameSound("..\\Sound\\girl.wav");
      }else if(gameData->score>500){
            PlayGameSound("..\\Sound\\blue.wav");
      }else if(gameData->score>400){
            PlayGameSound("..\\Sound\\red.wav");
      }else if(gameData->score>200){
            PlayGameSound("..\\Sound\\over_bak.wav");
            Sleep(1300);
      }else{
            PlayGameSound("..\\Sound\\over.wav");
      }
    }
    Sleep(1000);
    StopGameSound();
}

void Basic_setup()
{
    setTitle(TEXT("Snaker Game"));
    setWinSize(80,25);
    disableCurrsor();
}

void ReadyGame()
{
    Basic_setup();
    GameInitial();
    drawControlPanel();
    drawHelpPanel();
    //Afferent the operating function to the interface
    ControlPanelOperator Control_Op={
            drawHelpPanel,
            drawGamePanel,
            drawSettingPanel,
            drawExitPanel,
            StartGame

    };
    setControlPanelOperator(&Control_Op);
    setGameInfo(gameData->score,gameData->length,gameData->speed);
    //Binding control panel operation
    while(1){
        Control_Panel_Key_Bind();
        Sleep(100);
    }
}

void StartGame()
{
    Background_Music();
    //Surviving and withdrawing from the switch is not a real game.
    while(!CheckDead()&&getGameExit()!=1)
    {
        //Keystroke operation
        GamePanelKeyHandler();
        //Games do not run games for pause
        if(getGameSuspend()!=1) {
            //Food function
            EatFood();
            //Snake Move
            SnakeMove();
            //Update the game panel
            drawGamePanel();
            //Refresh speed delay
            int s_time = gameData->speed * 1000;
            Sleep(s_time);
        }
    }
    StopGameSound();
    PrintDeadInfo();
    ResetGame();
}

void Background_Music()
{
    Setting *setting = GetSettingData();
    int sound=rand()%2;
    if (setting->Background_music == 1) {
        if(sound==0){
            PlayGameSound("..\\Sound\\loopbg02.wav");
        }else{
            PlayGameSound("..\\Sound\\loopbg.wav");
        }

    }
}

void GameInitial()
{
    srand(time(NULL));
    Setting *setting = GetSettingData();
    if (gameData == NULL) {
        gameData = (GameData *) malloc(sizeof(GameData));
        memset(gameData, 0, sizeof(GameData));
        gameData->snake = NULL;
        gameData->snakeTail=NULL;
        gameData->food = NULL;
    }
    gameData->Map_Width = setting->Map_Width;
    gameData->Map_Height = setting->Map_Height;
    gameData->length = setting->snake_length;
    gameData->direction=setting->direction;
    if (gameData->snake == NULL) {
        SnakeInitial(setting);
    }
    if (gameData->food == NULL) {
        gameData->food = (Food *) malloc(sizeof(Food));
        FreshFoodInfo();
    }
    gameData->score = 0;
    gameData->speed = setting->snake_speed;
}

void FreshFoodInfo()
{
    gameData->food->x = rand() % gameData->Map_Width;
    gameData->food->y = rand() % gameData->Map_Height;
    gameData->food->Color = rand() % 0xF;
}

void SnakeInitial(Setting *setting)
{
    int i;
    for(i=setting->snake_length-1;i>=0;i--)
    {
        SnakeNode* node=(SnakeNode*)malloc(sizeof(SnakeNode));
        node->x=i;
        node->y=setting->snake_y;
        node->Color=setting->shake_color;
        node->next=NULL;
        node->prev=NULL;
        if(gameData->snake==NULL){
            //The header node points to the current node
            gameData->snake=node;
            //The tail node points to the current node
            gameData->snakeTail=node;
        }else{
            //The current node points to the next node
            gameData->snakeTail->next=node;
            //The next node points to the last node
            node->prev=gameData->snakeTail;
            //The tail node points to the next node
            gameData->snakeTail=node;
        }

    }
}

void SnakeMove()
{
    /**
     * The head node changes the coordinates according to the operation
     * The next node's coordinate is equal to the last node's coordinates.
     */
    //Save the current first coordinate
    int x=gameData->snake->x;
    int y=gameData->snake->y;
    PositionByDirection(&x, &y);
    //From the end, we get a node coordinate to the front.
    SnakeNode* loop=NULL;
    for(loop=gameData->snakeTail;loop->prev!=NULL;loop=loop->prev)
    {
        loop->x=loop->prev->x;
        loop->y=loop->prev->y;
    }
    //The new assignment in the head node.
    gameData->snake->x=x;
    gameData->snake->y=y;
}

void PositionByDirection(int *x, int *y)
{
    //Get new coordinate
    switch (gameData->direction)
    {
        case S_UP:
            (*y)--;
            if((*y) < 0){
                (*y) =gameData->Map_Height;
            }
            break;
        case S_DOWN:
            (*y)++;
            if((*y) > gameData->Map_Height){
                (*y) =0;
            }
            break;
        case S_LEFT:
            (*x)--;
            if((*x) < 0){
                (*x) =gameData->Map_Width;
            }
            break;
        case S_RIGHT:
            (*x)++;
            if((*x) > gameData->Map_Width){
                (*x) =0;
            }
            break;
        default:
            break;
    }
}

void EatFood()
{
    //The same position with food to eat food operation
    if(gameData->snake->x==gameData->food->x&&gameData->snake->y==gameData->food->y){
        //Eat effects
        Setting *setting = GetSettingData();
        if(setting->Eat_effects==1){
            EatEffects();
        }
        /**
         * List structure add snake
         */
        SnakeNode* node=(SnakeNode*)malloc(sizeof(SnakeNode));
        memset(node,0, sizeof(SnakeNode));
        node->prev=NULL;
        int x=gameData->snake->x;
        int y=gameData->snake->y;
        PositionByDirection(&x,&y);
        node->x=x;
        node->y=y;
        node->Color=gameData->food->Color;
        node->next=gameData->snake;
        gameData->snake->prev=node;
        gameData->snake=node;
        /**
        * Change information
        */
        gameData->length++;
        gameData->score+=10;
        if(gameData->score > 0 && gameData->score%20 && gameData->speed > 0.05){
            gameData->speed -= 0.02;
        }
        setGameInfo(gameData->score,gameData->length,gameData->speed);
        //Modify food information
        FreshFoodInfo();
    }

}

_Bool CheckDead()
{
    //If a snake with any head the same position of death
    SnakeNode* loop=NULL;
    for (loop = gameData->snake->next;loop!=NULL;loop=loop->next)
    {
        if(loop->x==gameData->snake->x&&loop->y==gameData->snake->y){
            return 1;  //death
        }
    }
    return 0;   //Existence
}

void EatEffects()
{
    PlayGameSound("..\\Sound\\eat.wav");
    Sleep(100);
    Background_Music();
}

void ResetGame()
{
    //Small data release
    SnakeNode* loop = NULL;
    for(loop = gameData->snakeTail->prev;loop!=NULL;loop=loop->prev){
        free(loop->next);
        loop->next = NULL;
    }
    // Release of the head
    free(gameData->snake);
    gameData->snake = NULL;
    gameData->snakeTail = NULL;
    //  Reset the game data
    Setting* setting = GetSettingData();
    gameData->length = setting->snake_length;
    gameData->speed = setting->snake_speed;
    gameData->score = 0;
    gameData->direction = setting->direction;
    FreshFoodInfo();
    SnakeInitial(setting);
    setGameInfo(gameData->score,gameData->length,gameData->speed);
    InitialGameControlInfo();
}