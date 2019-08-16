/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: SoundController.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/22.
> Functional  Renju sound controller
*******************************************************/
#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

class SoundController
{
public:
	static SoundController* getInstance();
	static void  destroyInstance();
	void PlayMusic();
	void PlayEffect();
	void PlayWin();
	void StopMusic();
	void PauseMusic();
	void PauseEffect();
private:
	SoundController(){}
	~SoundController(){}
	static SoundController* Instance;

};