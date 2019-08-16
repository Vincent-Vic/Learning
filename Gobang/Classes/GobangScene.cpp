/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangScene.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/18.
> Functional:  Gabang game scenes
*******************************************************/

#include "GobangScene.h"

Scene * GobangScene::createScene()
{
	return GobangScene::create();
}

bool GobangScene::init()
{
	if(!Scene::init())
		return false;
	auto listaner = EventListenerTouchOneByOne::create();
	listaner->setSwallowTouches(true);
	listaner->onTouchBegan = CC_CALLBACK_2(GobangScene::onTouchBegan,this);
	listaner->onTouchEnded = CC_CALLBACK_2(GobangScene::onTouchEnded, this);;
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listaner, this);
	_setGameHomeEnabled(true);
	_setCapitulateLock(false);
	_setTouchLock(false);
	visibleSize = Director::getInstance()->getVisibleSize();
	_InterfaceInit();
	_scheduleTime();


	return true;
}

void GobangScene::_scheduleTime()
{
	this->min = (int)GobangData::getInstance()->getGameTime();   //The number of minutes is set time of difficulty.
	if (this->min != 0) {
		this->sec = 0;   //The number of seconds is 0s.
		struct timeval now;
		gettimeofday(&now, NULL);
		this->oldTime = now.tv_sec;
		schedule(schedule_selector(GobangScene::update));
	}
	else {
		_Countdown->setString("infinite");
	}
}

void GobangScene::update(float dt)
{
		struct timeval now;
		gettimeofday(&now, NULL);
		int nowTime = now.tv_sec;   //Gets the time after calling the timer.
		if (this->min != 0 || this->sec != 0) { //Determine whether timing is not over.
			if (nowTime - this->oldTime == 1)			//Determine whether the time after calling the timer (which may have been called several times) is 1 s below the time before calling the timer
			{
				if (this->sec == 0) {
					this->min--;
					this->sec = 59;
					_Countdown->setString(String(Value(this->min).asString() + ":" + Value(this->sec).asString()).getCString());
				}
				else if (this->sec != 0) {
					this->sec--;
					_Countdown->setString(String(Value(this->min).asString()+":"+ Value(this->sec).asString()).getCString());
				}
				if(this->min==0&&this->sec==10){
					_Countdown->setColor(Color3B::RED);
				}
				this->oldTime = nowTime;   //Reset the time before calling the timer.
			}
		}
		else if (this->min == 0 && this->sec == 0) {  //Determine whether time ends.
			unschedule(schedule_selector(GobangScene::update));  //Cancel timer
			CCLOG("end!");
			_setCapitulateLock(true);
			_State->setString(Module::getInstance()->getCNByID(1022));
			_State->setColor(Color3B::BLACK);
		}
}

void GobangScene::_InterfaceInit()
{
	this->addChild(Module::getInstance()->createMaterial("Background/GameBack.jpg"));
	
	Borad = Module::getInstance()->createMaterial("Material/Board.png", Vec2(visibleSize / 2));
	Borad->setContentSize(Size(visibleSize .width, visibleSize.width));
	Borad->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(Borad, 3);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int count = GobangController::getInstance()->getChessBoard()->getWidth();
	Vec2 origins = Borad->getPosition() - Vec2(Borad->getContentSize().width / 2-15, Borad->getContentSize().height / 2-15);
	boardSize = Rect(origins.x, origins.y, Borad->getContentSize().width-30, Borad->getContentSize().height-30);
	
	_sprite = Sprite::create("Material/flag.png");
	_sprite->setVisible(false);
	_sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	Borad->addChild(_sprite, 1000);
	_MaterialInit();
	_ButtonInit();
}

void GobangScene::_ButtonInit()
{
	_Restart= Module::getInstance()->createControlButton("Button/Restart.png", "Button/Restart_Press.png", Vec2(visibleSize.width *0.6, visibleSize.height *0.95),0.2f);
	_Restart->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Restart->addClickEventListener(CC_CALLBACK_1(GobangScene::RestartCallBack, this));
	this->addChild(_Restart, 3);

	_Setting = Module::getInstance()->createControlButton("Button/Setting.png", "Button/Setting_Press.png",  Vec2(visibleSize.width *0.75, visibleSize.height *0.95), 0.2f);
	_Setting->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Setting->addClickEventListener(CC_CALLBACK_1(GobangScene::SettingCallBack, this));
	this->addChild(_Setting, 3);

	_Close = Module::getInstance()->createControlButton("Button/close.png", "Button/close_Press.png",  Vec2(visibleSize.width *0.9, visibleSize.height *0.95), 0.35f);
	_Close->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Close->addClickEventListener(CC_CALLBACK_1(GobangScene::RetuenDialogCallBack, this));
	this->addChild(_Close, 3);

	_TakeBack = Module::getInstance()->createControlButton("Button/Retract.png", "Button/Retract_Press.png",  Vec2(visibleSize.width *0.3, visibleSize.height *0.10f));
	_TakeBack->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_TakeBack->addClickEventListener(CC_CALLBACK_1(GobangScene::TakeBackCallBack, this));
	this->addChild(_TakeBack, 3);

	_Capitulate = Module::getInstance()->createControlButton("Button/Capitulate.png", "Button/Capitulate_Press.png",Vec2(visibleSize.width *0.7, visibleSize.height *0.10));
	_Capitulate->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Capitulate->addClickEventListener(CC_CALLBACK_1(GobangScene::CapitulateCallBack, this));
	this->addChild(_Capitulate, 3);
}

void GobangScene::_MaterialInit()
{
	auto Clock = Module::getInstance()->createMaterial("Material/clock.png", Vec2(visibleSize.width *0.05, visibleSize.height *0.95));
	Clock->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Clock->setScale(0.05f);
	this->addChild(Clock, 3);

	auto ClockInfo = Sprite::create("Material/TitleBox.png");
	ClockInfo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	ClockInfo->setPosition(Vec2(visibleSize.width *0.08, visibleSize.height *0.95));
	ClockInfo->setScale(0.35f);
	this->addChild(ClockInfo, 3);

	_Countdown= Module::getInstance()->createLabel("", Vec2(visibleSize.width *0.25, visibleSize.height *0.95));
	_Countdown->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Countdown->setSystemFontSize(36);
	_Countdown->setColor(Color3B::WHITE);
	this->addChild(_Countdown,4);

	auto StatusBar = Sprite::create("Material/StatusBar.png");
	StatusBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	StatusBar->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height *0.83));
	StatusBar->setContentSize(Size(visibleSize.width-50,50));
	//StatusBar->setScale(0.3f);
	this->addChild(StatusBar, 3);
	_State = Module::getInstance()->createLabel(Module::getInstance()->getCNByID(1023), Vec2(visibleSize.width *0.5, visibleSize.height *0.83));
	_State->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_State->setSystemFontSize(36);
	this->addChild(_State, 4);

}

void GobangScene::_setGameHomeEnabled(bool switchs)
{
	enabled = switchs;
}

bool GobangScene::_getGameHomeEnabled()
{
	return enabled;
}

void GobangScene::_setCapitulateLock(bool Capitulate)
{
	_CapitulateLock = Capitulate;
}

bool GobangScene::_getCapitulateLock()
{
	return _CapitulateLock;
}

void GobangScene::_setTouchLock(bool TouchLock)
{
	_TouchLock = TouchLock;
}

bool GobangScene::_getTouchLock()
{
	return _TouchLock;
}

bool GobangScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void GobangScene::onTouchEnded(Touch * touch, Event * event)
{
	if (_getCapitulateLock()|| _getTouchLock())return;
	Vec2 position = touch->getLocation();
	log("position(%d,%d)", position.x, position.y);
	if (boardSize.containsPoint(position))
	{
		Vec2 relative = position- Vec2(18, visibleSize.height*0.455);
		float val = relative.x / _padding;
		int row = int(val);
		if (val > row) row++;

		val = relative.y / _padding;
		int cols = int(val);
		if (val > cols) cols++;

		//The fall
		ChessPieceType type = GobangController::getInstance()->getChessType();
		bool result = GobangController::getInstance()->palyChess(type, row, cols);
		//The success of the fall
		if (result)
		{
			if(GobangData::getInstance()->getEffect())
				SoundController::getInstance()->PlayEffect();
			//Show a chess genius
			createChessNode(type, row, cols);

			//Deciding whether to win or not
			if (GobangController::getInstance()->judgeWin(type, row, cols))
			{
				Results = false;
				_setCapitulateLock(true);
				if (type == White) {
					_State->setString(Module::getInstance()->getCNByID(1021));
					Results = false;
				}
				else if (type == Black) {
					_State->setString(Module::getInstance()->getCNByID(1020));
					Results = true;
				}
				auto ResultsCallback = CallFunc::create([this]() {
					RestartGobang();
					auto gameResults = GameResults::create();
					gameResults->setResults(Results);
					//Fade in effect
					Director::getInstance()->pushScene(TransitionFade::create(0.2f, gameResults, Color3B::GRAY));
				});
				this->runAction(Sequence::create(
					DelayTime::create(2.0f),
					ResultsCallback,
					nullptr
				));
				
				
			}
			else {
				if (type == Black)
							{
								_State->setString(Module::getInstance()->getCNByID(1019));
							}
				else {
								_State->setString(Module::getInstance()->getCNByID(1018));
				}
			}
			
		}

	}
}

void GobangScene::RestartGobang()
{
	//Restart the game response
	if (!_getGameHomeEnabled())
		return;
	GobangController::destroyInstance();

	for (auto node : prt_allChesses) {
		node->removeFromParent();
	}
	//Hide the logo
	_sprite->setVisible(false);

	GobangController::getInstance();
	_State->setString(Module::getInstance()->getCNByID(1023));
	_Countdown->setColor(Color3B::WHITE);
	_State->setColor(Color3B::BLACK);
	_scheduleTime();
	_setCapitulateLock(false);
	_setTouchLock(false);
}

void GobangScene::RestartCallBack(cocos2d::Ref * pSender)
{
	RestartGobang();
}

void GobangScene::SettingCallBack(cocos2d::Ref * pSender)
{
	//Setting the response
	if (!_getGameHomeEnabled())
		return;
	this->_setTouchLock(true);
	GameSetting* Setting = GameSetting::create();
	if (Setting) {
		_setGameHomeEnabled(false);
	}
	else {
		ResErrHandling(true, "0xST200002");
	}
	Setting->SetMessage(&_TouchLock);
	Setting->SetMessagees(&enabled);
	Setting->_SetDifficultyEnabled(false);
	this->addChild(Setting, 4);
}

void GobangScene::TakeBackCallBack(cocos2d::Ref * pSender)
{
	if (this->_getCapitulateLock()|| !_getGameHomeEnabled())
		return;
	ChessPieceType type = GobangController::getInstance()->getChessType();
	if (type == Black) {
		_State->setString(Module::getInstance()->getCNByID(1027));
	}
	else if (type == White) {
		_State->setString(Module::getInstance()->getCNByID(1028));
	}
	bool TakeBackResult = false;
	if (prt_allChesses.size() > 0) {
		TakeBackResult = GobangController::getInstance()->GobangTakeBack();
		if (TakeBackResult) {
			Borad->removeChildByTag(prt_allChesses.at(prt_allChesses.size()-1)->getTag());
			if (prt_allChesses.size() > 3) {
				_sprite->setPosition(prt_allChesses.at(prt_allChesses.size() - 2)->getPosition());
			}
			else {
				_sprite->setVisible(false);
			}
			prt_allChesses.popBack();
		}
	}
	if (!TakeBackResult) {
		_State->setString(Module::getInstance()->getCNByID(1029));
	}
	
}

void GobangScene::CapitulateCallBack(cocos2d::Ref * pSender)
{
	if (!_getGameHomeEnabled())
		return;
	_setCapitulateLock(true);
	ChessPieceType type = GobangController::getInstance()->getChessType();
	if (type == Black) {
		_State->setString(Module::getInstance()->getCNByID(1025));
	}
	else if (type == White) {
		_State->setString(Module::getInstance()->getCNByID(1026));
	}
}

void GobangScene::RetuenDialogCallBack(cocos2d::Ref * pSender)
{
	//return Home the response
	if (!_getGameHomeEnabled())
		return;
	_setTouchLock(true);
	_setGameHomeEnabled(false);
	dialog = Layer::create();
	dialog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	dialog->setContentSize(Size(visibleSize.width*0.7, visibleSize.height*0.2));

	auto bg = Module::getInstance()->createMaterial("Background/Dialog.png",visibleSize/2);
	bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bg->setContentSize(dialog->getContentSize());
	dialog->addChild(bg, 2000);

	auto label = Module::getInstance()->createLabel(Module::getInstance()->getCNByID(1024),Vec2(visibleSize/2 )+Vec2(0,20));
	label->setSystemFontSize(24);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	dialog->addChild(label, 2000);

	auto yes = Module::getInstance()->createControlButton("Button/OK.png", "Button/OK_Press.png", Vec2(visibleSize / 2) -Vec2(90,50));
	yes->setScale(0.3);
	dialog->addChild(yes, 2000);
	yes->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type) {
		//Return home page response
		auto RestartCallback = CallFunc::create([this]() {

			auto GameHome = GameHome::create();
			//Fade in the switching effect
			Director::getInstance()->pushScene(TransitionFade::create(0.6f, GameHome, Color3B::GRAY));
		});
		this->runAction(Sequence::create(
			RestartCallback,
			nullptr
		));
	});
	auto no = Module::getInstance()->createControlButton("Button/Cancel.png", "Button/Cancel_Press.png", yes->getPosition()+Vec2(100,0));
	no->setScale(0.3);
	dialog->addChild(no,2000);
	no->addTouchEventListener([&](Ref* ref, ui::Widget::TouchEventType type) {
		
		dialog->removeAllChildren();
		auto callback = CallFunc::create([this]() {
			_setTouchLock(false);
			_setGameHomeEnabled(true);
		});

		this->runAction(Sequence::create(
			DelayTime::create(0.1f),
			callback,
			nullptr
		));
	});
	this->addChild(dialog, 2000);
}

void GobangScene::createChessNode(int type, int x, int y)
{
	//The dot matrix starts from 0 and 0.
	x--;
	y--;

	Sprite* chessNode = Sprite::create(String::createWithFormat("Material/%d.png", type)->getCString());
	chessNode->setPosition(boardSize.origin + Vec2(_padding * (x + 0.5), _padding * (y + 0.5))+Vec2(4,-7.5));
	chessNode->setTag(x * 100 + y);
	Borad->addChild(chessNode, 4, x * 100 + y);
	prt_allChesses.pushBack(chessNode);

	//Identifying the current pieces
	if (!_sprite->isVisible())
	{
		_sprite->setVisible(true);
	}
	_sprite->setPosition(chessNode->getPosition() + Vec2(0, 10));
	_sprite->stopAllActions();
	_sprite->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(.5f, Vec2(0, -10)),
		MoveBy::create(.5f, Vec2(0, 10)),
		nullptr)));
}