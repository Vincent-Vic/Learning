/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GamePrologue.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Responsible for opening and calling the game
*******************************************************/
#include "GamePrologue.h"

cocos2d::Scene * GamePrologue::createScene()
{
	return GamePrologue::create();
}

bool GamePrologue::init()
{
	if(!Scene::init())
		return false;
	//Data initialization
	GobangData::getInstance()->setBackMusic(true);
	GobangData::getInstance()->setEffect(true);
	GobangData::getInstance()->setGameTime(5.0f);
	if(GobangData::getInstance()->getBackMusic())
		SoundController::getInstance()->PlayMusic();
	this->addChild(Module::getInstance()->createMaterial("Background/Prelude.jpg"));
	

	this->schedule([&](float dit) {
		//When the I exceeds the length, the dispatcher is cancelled.
			this->unschedule("schedule_callback");
			auto GameHome = GameHome::create();
			Director::getInstance()->pushScene(TransitionFade::create(0.6f, GameHome, Color3B::GRAY));
	}, 0.8f, "schedule_callback");
	return true;
}
