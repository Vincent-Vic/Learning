/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GamePrologue.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Responsible for opening and calling the game
*******************************************************/
#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "GameHome.h"
#include "Module.h"
#include "GobangData.h"
#include "SoundController.h"

class GamePrologue : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GamePrologue);
};