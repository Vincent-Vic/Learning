/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangData.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  GobangData Data
*******************************************************/
#pragma once


 class GobangData 
{
public:
	static GobangData* getInstance();
	static void  destroyInstance();
	void setBackMusic(bool Back);
	bool getBackMusic();
	void setEffect(bool Effect);
	bool getEffect();
	void setGameTime(float time);
	float getGameTime();
private:
	static GobangData* Instance;
	bool _BackMusic;
	bool _Effect;
	float _Time;
};