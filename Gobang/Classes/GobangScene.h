/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangScene.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/18.
> Functional:  Gabang game scenes
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
typedef std::function<void()> Updata;

#include "GlobalSchedule.h"
#include "Module.h"
#include "Error.h"
#include "GameSetting.h"
#include "GobangData.h"
#include "GobangController.h"
#include "GameHome.h"
#include "GameResults.h"

class GobangScene :public Scene
{
public:
	CREATE_FUNC(GobangScene);
	static Scene* createScene();
	//初始化数据和界面
	virtual bool init();

private:
	//Interface
	int oldTime;  //调用schedule定时器前的时间
	int min;      //定时的分钟数
	int sec;      //定时的秒数
	void _scheduleTime();
	virtual void update(float dt);  //schedule定时器调用的方法

	Size visibleSize;
	//**_State**//
	//Controls whether other buttons respond
	bool enabled;
	void _setGameHomeEnabled(bool switchs);
	bool _getGameHomeEnabled();
	bool _CapitulateLock;
	void _setCapitulateLock(bool Capitulate);
	bool _getCapitulateLock();
	bool _TouchLock;
	void _setTouchLock(bool TouchLock);
	bool _getTouchLock();

	bool Results;
	Label* _State;
	/**button**/
	Button* _Restart;
	Button* _Setting;
	Button* _Close;
	Button* _TakeBack;
	Button* _Capitulate;
	Label* _Countdown;
	/**Interface**/
	void _InterfaceInit();
	void _ButtonInit();
	void _MaterialInit();
	//controller
	Rect boardSize;
	//Record the width of the grid
	const int _padding=24;
	//Create pieces
	void createChessNode(int type, int x, int y);
	//Record background
	Node * prt_bg;
	//Record the size of the board
	Rect prt_boardSize;
	//Pawn identity
	Sprite* _sprite;
	Sprite* Borad;
	//Record the data of the pieces
	Vector<Node*> prt_allChesses;
	//callback
	bool onTouchBegan(Touch*touch, Event* event);
	void onTouchEnded(Touch*touch, Event* event);
	void RestartGobang();
	//Return to the face box on the homepage 
	void RestartCallBack(cocos2d::Ref * pSender);
	void SettingCallBack(cocos2d::Ref * pSender);
	void TakeBackCallBack(cocos2d::Ref * pSender);
	void CapitulateCallBack(cocos2d::Ref * pSender);
	Layer* dialog;
	void RetuenDialogCallBack(cocos2d::Ref * pSender);
};