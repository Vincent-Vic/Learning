/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameHome.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by  Vincent Vic  on 2018/8/15.
> Functional  Guide the game to start and pass the data to the game
*******************************************************/
#include "GameHome.h"

cocos2d::Scene * GameHome::createScene()
{
	return GameHome::create();
}

bool GameHome::init()
{
	if (!Scene::init())
		return false;
	visiable = Director::getInstance()->getVisibleSize();
	_setClickLoak(false);
	_InterfaceInit();
	return true;
}

void GameHome::Game()
{
	auto gobangScene = GobangScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.2f, gobangScene, Color3B::GRAY));
}

void GameHome::_setClickLoak(bool switchs)
{
	_ClickLock = switchs;
}

bool GameHome::_getClickLock()
{
	return _ClickLock;
}

void GameHome::PlayLoading()
{
	auto bg = Module::getInstance()->createMaterial("Background/GameBack.jpg");
	this->addChild(bg);
	gameLoadingBar = LoadingBar::create();
	gameLoadingBar->setContentSize(Size(visiable.width, gameLoadingBar->getContentSize().height));
	gameLoadingBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	gameLoadingBar->setPosition(visiable / 2);
	bg->addChild(gameLoadingBar);

	gameLoadingBar->loadTexture("Material/LoadingBar.png");
	ResErrHandling(!gameLoadingBar, "0xPB300002");
	gameLoadingBar->setPercent(0);
	gameLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	Loading = Sprite::create("Material/load.png");
	ResErrHandling(!Loading, "0xPB300003");
	Loading->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Loading->setPosition(Vec2(visiable / 2) + Vec2(-40, 30));
	bg->addChild(Loading);

	static int i = 0;
	this->schedule([&](float dit) {
		i++;
		gameLoadingBar->setPercent(gameLoadingBar->getPercent() + 1);
		//When the I exceeds the length, the dispatcher is cancelled.*/
		if (i == 100) {
			i = 0;
			Game();
			this->removeChild(bg);
			this->unschedule("schedule_callback");
			return;
		}
	}, 0.012f, "schedule_callback");
}

void GameHome::_InterfaceInit()
{
	this->addChild(Module::getInstance()->createMaterial("Background/HomeBg.jpg"));
	Vec2 base = visiable /2;
	//Start Game Button
	_StartGame= Module::getInstance()->createControlButton("Button/Start.png", "Button/Start_Press.png",  base);
	_StartGame->setPosition(_StartGame->getPosition()+Vec2(-_StartGame->getContentSize().width *0.4, -_StartGame->getContentSize().height*0.25));
	_StartGame->addClickEventListener(CC_CALLBACK_1(GameHome::_StartCallback, this));
	this->addChild(_StartGame);

	//Setting Game Button
	_SettingGame = Module::getInstance()->createControlButton("Button/Setting.png", "Button/Setting_Press.png",base);
	_SettingGame->setPosition(_SettingGame->getPosition() + Vec2(_SettingGame->getContentSize().width *0.1, -_SettingGame->getContentSize().height*0.6));
	_SettingGame->addClickEventListener(CC_CALLBACK_1(GameHome::_SettingCallback, this));
	this->addChild(_SettingGame);

	//Exit Game Button
	_ExitGame = Module::getInstance()->createControlButton("Button/Exit.png", "Button/Exit_Press.png", base );
	_ExitGame->setPosition(_ExitGame->getPosition() + Vec2(-_ExitGame->getContentSize().width *0.4, -_ExitGame->getContentSize().height*0.8));
	_ExitGame->addClickEventListener(CC_CALLBACK_1(GameHome::_ExitCallback, this));
	this->addChild(_ExitGame);
	
	//About Prep
	_AboutPrep = Module::getInstance()->createControlButton("Button/About.png", "Button/About_Press.png", Vec2(visiable) - Vec2(45, 10),0.4f);
	_AboutPrep->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_AboutPrep->addClickEventListener(CC_CALLBACK_1(GameHome::_AboutPrepCallback, this));
	this->addChild(_AboutPrep);
}

void GameHome::_AboutPrepCallback(cocos2d::Ref * pSender)
{
	if (_getClickLock())
		return;
	Size AuthorSize = Size(visiable.width, visiable.height / 2);
	Author = Layer::create();
	Author->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	Author->setPosition(visiable/2);
	Author->setContentSize(AuthorSize);

	Sprite* info = Module::getInstance()->createMaterial("Material/About_Author.png");
	info->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	info->setContentSize(Author->getContentSize());
	Author->addChild(info,2);
	
	auto CloseAuthor = Module::getInstance()->createCloseButton(info->getContentSize() / 2.7, 0.2);
	CloseAuthor->addClickEventListener(CC_CALLBACK_1(GameHome::_CloseAuthorCallback, this));
	Author->addChild(CloseAuthor,2);
	this->addChild(Author);
	
	
}

void GameHome::_CloseAuthorCallback(cocos2d::Ref * pSender)
{

	_setClickLoak(false); 
	Author->removeAllChildren();
	this->removeChild(Author, true);
}

void GameHome::_StartCallback(cocos2d::Ref * pSender)
{
	if (_getClickLock())
		return;
	PlayLoading();
}

void GameHome::_SettingCallback(cocos2d::Ref * pSender)
{
	if (_getClickLock())
		return;
	GameSetting* Setting = GameSetting::create();
	if (Setting) {
		_setClickLoak(false);
	}
	else {
		ResErrHandling(true, "0xST200002");
	}
	Setting->SetMessage(&_ClickLock);
	this->addChild(Setting);

}

void GameHome::_ExitCallback(cocos2d::Ref * pSender)
{
	if (_getClickLock())
		return;
	Director::getInstance()->end();
}
