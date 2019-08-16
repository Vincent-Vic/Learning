/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameSetting.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Game setup module
*******************************************************/
#include "GameSetting.h"



bool GameSetting::init()
{
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_InterfaceInit();
	return true;
}

void GameSetting::SetMessage(bool * en)
{
	enabled = en;
	*enabled = true;
}

void GameSetting::SetMessagees(bool * en)
{
	enabledes = en;
}

void GameSetting::_SetDifficultyEnabled(bool enabled)
{
	for (int i=0; i < 4; i++) {
		_Difficulty[i]->setEnabled(enabled);
	}
}

void GameSetting::_InterfaceInit()
{
	Size visiable = Director::getInstance()->getVisibleSize();
	Size SettingSize = Size(visiable.width, visiable.height / 2);
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->setPosition(visiable / 2);
	this->setContentSize(SettingSize);

	Sprite* back = Module::getInstance()->createMaterial("Background/Dialog.png");
	back->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	back->setContentSize(this->getContentSize());
	this->addChild(back, 2);

	auto CloseAuthor = Module::getInstance()->createCloseButton(back->getContentSize() / 2.7, 0.2f);
	CloseAuthor->addClickEventListener(CC_CALLBACK_1(GameSetting::_CloseSettingCallback, this));
	this->addChild(CloseAuthor, 2);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 MusicVec = Vec2(-visiable.width/3,-visiable.height/140);
	_BackMusicBox = Module::getInstance()->createCheckBox(GobangData::getInstance()->getBackMusic(), MusicVec);
	_BackMusicBox->setPosition(_BackMusicBox->getPosition()+Vec2(0, _BackMusicBox->getContentSize().height));
	this->addChild(_BackMusicBox,3);
	_BackMusicBox->addEventListener([&](Ref* ref, ui::CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED)
		{
			GobangData::getInstance()->setBackMusic(true);
			SoundController::getInstance()->PlayMusic();
		}
		else {
			GobangData::getInstance()->setBackMusic(false);
			SoundController::getInstance()->PauseMusic();
		}

	});
	_BackMusicLabel = Module::getInstance()->createLabel("Background Music", MusicVec);
	_BackMusicLabel->setPosition(_BackMusicBox->getPosition() + Vec2(_BackMusicBox->getContentSize().width*0.3,2));
	this->addChild(_BackMusicLabel,3);

	_EffectBox = Module::getInstance()->createCheckBox(GobangData::getInstance()->getEffect(), MusicVec);
	this->addChild(_EffectBox,3);
	_EffectBox->addEventListener([&](Ref* ref, ui::CheckBox::EventType type) {
			if (type == CheckBox::EventType::SELECTED)
			{
				GobangData::getInstance()->setEffect(true);
				SoundController::getInstance()->PlayEffect();
			}
			else {
				GobangData::getInstance()->setEffect(false);
				SoundController::getInstance()->PauseEffect();
			}

		});
	
	_EffectLabel = Module::getInstance()->createLabel("Effect", MusicVec);
	_EffectLabel->setPosition(_EffectBox->getPosition() + Vec2(_EffectBox->getContentSize().width*0.3, 2));
	this->addChild(_EffectLabel,3);
	
	auto MusicTitle= Module::getInstance()->createLabel("Sound Settings", _BackMusicBox->getPosition()+Vec2(0,_BackMusicBox->getContentSize().height));
	MusicTitle->setSystemFontSize(15.5);
	MusicTitle->setColor(Color3B::RED);
	this->addChild(MusicTitle,3);

	auto DifficultyTitle = Module::getInstance()->createLabel("Difficulty setting", MusicTitle->getPosition() + Vec2(MusicTitle->getContentSize().width+15, 0));
	DifficultyTitle->setSystemFontSize(15.5);
	DifficultyTitle->setColor(Color3B::RED);
	this->addChild(DifficultyTitle, 3);

	_Difficulty[0] = Module::getInstance()->createRadioButton(DifficultyTitle->getPosition()-Vec2(0, _BackMusicBox->getPosition().y+10),0);
	this->addChild(_Difficulty[0], 3);

	_degree[0] = Module::getInstance()->createLabel("Exercise", MusicVec);
	_degree[0]->setPosition(_Difficulty[0]->getPosition() + Vec2(_BackMusicBox->getContentSize().width*0.7, 2));
	this->addChild(_degree[0], 3);

	_Difficulty[1] = Module::getInstance()->createRadioButton(Vec2(_Difficulty[0]->getPosition().x, _EffectBox->getPosition().y),10);
	this->addChild(_Difficulty[1], 3);

	_degree[1] = Module::getInstance()->createLabel("Primary", MusicVec);
	_degree[1]->setPosition(_Difficulty[1]->getPosition() + Vec2(_BackMusicBox->getContentSize().width*0.7, 2));
	this->addChild(_degree[1], 3);

	_Difficulty[2] = Module::getInstance()->createRadioButton(_Difficulty[1]->getPosition() -Vec2(0, _BackMusicBox->getContentSize().height-10),5);
	this->addChild(_Difficulty[2], 3);

	_degree[2] = Module::getInstance()->createLabel("Medium", MusicVec);
	_degree[2]->setPosition(_Difficulty[2]->getPosition() + Vec2(_BackMusicBox->getContentSize().width*0.7, 2));
	this->addChild(_degree[2], 3);

	_Difficulty[3] = Module::getInstance()->createRadioButton(_Difficulty[2]->getPosition() - Vec2(0, _BackMusicBox->getContentSize().height - 10),3);
	this->addChild(_Difficulty[3], 3);

	_degree[3] = Module::getInstance()->createLabel("Superior ", MusicVec);
	_degree[3]->setPosition(_Difficulty[3]->getPosition() + Vec2(_BackMusicBox->getContentSize().width*0.7, 2));
	this->addChild(_degree[3], 3);
	for (int i = 0; i < 4; i++)
	{
		_Difficulty[i]->addClickEventListener([this](Ref* ref) {

			auto Radio = dynamic_cast<RadioButton*>(ref);
			for (int i = 0; i < 4; i++)
			{
				_Difficulty[i]->setSelected(false);
			}
			Radio->setSelected(true);
			GobangData::getInstance()->setGameTime((float)Radio->getTag());
		});
	}
}


void GameSetting::_ChangeStateInterface()
{

	for (int i = 0; i < 4; i++)
	{
		if (_Difficulty[i]->getTag() == (int)GobangData::getInstance()->getGameTime()) {
			_Difficulty[i]->setSelected(true);
		}
		else {
			_Difficulty[i]->setSelected(false);
		}
		
	}
	_BackMusicBox->setSelectedState(GobangData::getInstance()->getBackMusic());
	_EffectBox->setSelectedState(GobangData::getInstance()->getEffect());
}

void GameSetting::_CloseSettingCallback(cocos2d::Ref * pSender)
{
	this->removeAllChildren();
	if(enabled)
		*enabled = false;
	if (enabledes)
		*enabledes = true;
}