/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameHome.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Guide the game to start and pass the data to the game
*******************************************************/

#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "ui/UIButton.h"
using namespace ui;
#include "GameSetting.h"
#include "GobangData.h"
#include"GameLoading.h"
#include "GameResults.h"
#include "Module.h"
#include "Error.h"

class GameHome : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameHome);
	
private:
	
	Button * _StartGame;
	Button * _SettingGame;
	Button * _ExitGame;
	Button * _AboutPrep;
	//GameSetting * Setting;
	Layer* Author;
	Size visiable;
	void _InterfaceInit();
	// a selector callback
	void _StartCallback(cocos2d::Ref* pSender);
	void _SettingCallback(cocos2d::Ref* pSender);
	void _ExitCallback(cocos2d::Ref* pSender);
	void _AboutPrepCallback(cocos2d::Ref* pSender); 
	void _CloseAuthorCallback(cocos2d::Ref* pSender);
	//Can the control button be clicked?
	bool _ClickLock;
	void _setClickLoak(bool switchs);
	bool _getClickLock();

	//Load component
	Sprite*  LoadingBackground;
	Sprite*  Loading;
	LoadingBar* gameLoadingBar;
	void PlayLoading();
	//play game
	void Game();
};