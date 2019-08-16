/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameSetting.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Game setup module
*******************************************************/

#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include"ui/CocosGUI.h"
using namespace ui;

#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;


#include "GobangData.h"
#include "GameHome.h"
#include "Module.h"
#include "Error.h"
#include "SoundController.h"

typedef std::function<void()> Lock;
class GameSetting : public cocos2d::Layer
{
public:
	virtual bool init();
	void SetMessage(bool* en);
	void SetMessagees(bool* en);
	void _SetDifficultyEnabled(bool enabled);
	CREATE_FUNC(GameSetting);
private:
	bool* enabled;
	bool* enabledes;
	CheckBox* _BackMusicBox;
	CheckBox* _EffectBox;
	RadioButton* _Difficulty[4];
	Label* _degree[4];
	Label* _BackMusicLabel;
	Label* _EffectLabel;
	void _InterfaceInit();
	void _ChangeStateInterface();
	void _CloseSettingCallback(cocos2d::Ref* pSender);
};