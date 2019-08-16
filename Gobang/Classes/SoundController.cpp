/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: SoundController.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/22.
> Functional  Renju sound controller
*******************************************************/

#include "SoundController.h"
SoundController* SoundController::Instance=nullptr;
SoundController * SoundController::getInstance()
{
	if (!Instance) {
		Instance = new SoundController();
	}
	return Instance;
}

void SoundController::destroyInstance()
{
	if (Instance) {
		delete Instance;
		Instance = nullptr;
	}
}

void SoundController::PlayMusic()
{
	srand((unsigned)time(NULL));
	int random = rand() % 4;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String("music/bgMusic_"+ Value(random).asString()+".mp3").getCString(), true);
}

void SoundController::PlayEffect()
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
	SimpleAudioEngine::getInstance()->playEffect("music/effect.wav",false,1,0.5,1);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.f);
}

void SoundController::PlayWin()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("win_game.mp3", true);
}

void SoundController::StopMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}

void SoundController::PauseMusic()
{
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundController::PauseEffect()
{
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}
