/******************************************************
    > File Name: GameData.h
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by  Vincent·Vic  on 2018/4/6.
    > Functional： Game Data declaration
*******************************************************/

#ifndef RERTO_SNAKER_GAMEDATA_H
#define RERTO_SNAKER_GAMEDATA_H

/**
 * The snake node structure
 */
typedef struct _snake_node{
    /**
     * coordinate
     */
    int x;
    int y;
    //Color
    int Color;
    //The formal definition of the snake chain
    struct _snake_node* prev;
    struct _snake_node* next;
}SnakeNode;

/**
 * Food structure
 */
typedef struct _food{
    /**
    * coordinate
    */
    int x;
    int y;
    //Color
    int Color;
}Food;

/**
 *  Snake Moving direction
 */
typedef enum _snake_direction{
    S_UP='w',   //Up
    S_DOWN='s', //Down
    S_LEFT='a', //left
    S_RIGHT='d' //right
}SnakeDirection;

/**
 * Game Data structure
 */
typedef struct _game_data{
    int score;
    int length;
    double speed;
    //Map size
    int Map_Width;
    int Map_Height;
    SnakeNode* snake;   //snake
    SnakeNode* snakeTail;
    Food* food;
    SnakeDirection direction;
}GameData;

#endif //RERTO_SNAKER_GAMEDATA_H