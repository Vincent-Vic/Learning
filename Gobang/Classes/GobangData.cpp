/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangData.cpp
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Gobang Data
*******************************************************/

#include "GobangData.h"
GobangData* GobangData::Instance=nullptr;
GobangData * GobangData::getInstance()
{
	if (!Instance)
	{
		Instance = new GobangData();
	}
	return Instance;
}

void GobangData::destroyInstance()
{
	if (Instance)
	{
		delete Instance;
		Instance=nullptr;
	}
}

void GobangData::setBackMusic(bool Back)
{
	_BackMusic= Back;
}

bool GobangData::getBackMusic()
{
	return _BackMusic;
}

void GobangData::setEffect(bool Effect)
{
	_Effect = Effect;
}

bool GobangData::getEffect()
{
	return _Effect;
}

void GobangData::setGameTime(float time)
{
	_Time=time;
}

float GobangData::getGameTime()
{
	return _Time;
}
