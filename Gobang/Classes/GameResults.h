/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameResults.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/17.
> Functional:  Game Results
*******************************************************/
#pragma once

#include "cocos2d.h"

USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;
#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;
#include "Module.h"
#include "Error.h"
#include "GameHome.h"
#include "GobangScene.h"
class GameResults :public Scene
{
public:
	CREATE_FUNC(GameResults);
	virtual bool init();
	void setResults(bool Results);
private:
	void InterfaceInit();
	Size visibleSize;
	bool _Results;
	Label* results;
	void Updata();
	Label* createInformation();
	map<int, Value>prt_cnWords;
	string prt_content;
	Button* _Restart;
	Button* _Home;
	//Card
	Button * _Card;
	//Card Sprite
	Sprite* _spCard;
	//Card appearance
	void cardShow();
	//Click card flip
	void getCard();
	//Animated playback
	void playAnimate();
};