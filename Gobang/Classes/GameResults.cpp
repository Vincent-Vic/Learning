/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GameResults.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/17.
> Functional:  Game Results
*******************************************************/
#include "GameResults.h"

bool GameResults::init()
{
	if (!Scene::init())
		return false;
	if (GobangData::getInstance()->getBackMusic()) {
		SoundController::getInstance()->StopMusic();
		SoundController::getInstance()->PlayWin();
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	_Results = false;
	//add Background
	Sprite* sp = Module::getInstance()->createMaterial("Background/GameBack.jpg");
	this->addChild(sp, 1);
	//add Card
	_Card = Button::create("card/card.jpg", "card/card.jpg", "card/card.jpg");
	_Card->setPosition(Vec2(visibleSize/2)+Vec2(0,50));
	_Card->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Card->setScale(0.1f);
	_Card->addClickEventListener([&](Ref* node) {
		_Card->setEnabled(false);
		//Click card flip
		getCard();
	});
	this->addChild(_Card, 2);
	//Card appearance
	cardShow();
	setResults(true);
	InterfaceInit();
	
	return true;
}

void GameResults::InterfaceInit()
{
	_Restart = Module::getInstance()->createControlButton("Button/Restart.png", "Button/Restart_Press.png",  Vec2(visibleSize.width *0.3, visibleSize.height *0.2));
	_Restart->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_Restart->addClickEventListener([&](Ref* node) {
		//Restart game response

		auto RestartCallback = CallFunc::create([this]() {

			auto gobangScene = GobangScene::create();
			//Fade in effect
			Director::getInstance()->pushScene(TransitionFade::create(0.2f, gobangScene, Color3B::GRAY));
			if (GobangData::getInstance()->getBackMusic()) {
				SoundController::getInstance()->StopMusic();
				SoundController::getInstance()->PlayMusic();
			}
		});
		this->runAction(Sequence::create(
			RestartCallback,
			nullptr
		));
	});
	this->addChild(_Restart,2);

	_Home = Module::getInstance()->createControlButton("Button/Home.png", "Button/Home_Press.png",  Vec2(visibleSize.width *0.7, visibleSize.height *0.2));
	_Home->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(_Home,2);
	_Home->addClickEventListener([&](Ref* node) {
		//return Home
		auto RestartCallback = CallFunc::create([this]() {
			auto GameHome = GameHome::create();
			Director::getInstance()->pushScene(TransitionFade::create(0.6f, GameHome, Color3B::GRAY));
			if (GobangData::getInstance()->getBackMusic()) {
				SoundController::getInstance()->StopMusic();
				SoundController::getInstance()->PlayMusic();
			}
		});
		this->runAction(Sequence::create(
			RestartCallback,
			nullptr
		));
		
	});

	
}

void GameResults::setResults(bool Results)
{
	this->_Results = Results;
	Updata();
}

void GameResults::Updata()
{
	results = Module::getInstance()->getInstance()->createLabel("", Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height - 60));
	results->setSystemFontSize(36);
	results->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(results, 3);
	if (this->_Results) {
		results->setString(Module::getInstance()->getCNByID(1020));
	}
	else {
		results->setString(Module::getInstance()->getCNByID(1021));
	}
	
	
}

Label* GameResults::createInformation()
{
	auto configData = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
	for (auto valPair : configData) {
		int Key = atoi(valPair.first.c_str());
		Value val = valPair.second;
		prt_cnWords.insert(pair<int, Value>(Key, val));

	}
	srand((unsigned)time(NULL));
	int random = rand() % 18 + 1000;
	auto label1 = Label::createWithSystemFont(prt_cnWords.at(random).asString(), "¿¬Ìå", 56);
	ResErrHandling(!label1, "0xPB600007");
	label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label1->setPosition(Vec2(visibleSize.width/2, 120));
	return label1;
}

void GameResults::cardShow()
{
	//Flip card animation
	auto rotateAction = RotateTo::create(0.5f, 2160);
	auto scaleAction = ScaleTo::create(0.5f, 0.5f);
	//Animated playback
	_Card->runAction(Spawn::createWithTwoActions(rotateAction, scaleAction));
}

void GameResults::getCard()
{
	//Horizontal zoom in, loading card surface and frame animation.
	auto scaleXAction = ScaleTo::create(0.5f, 0, 0.5f);
	auto loadText = CallFunc::create([this]() {
		Label* text = createInformation();
		_Card->addChild(text, 4);
	});
	auto callback = CallFunc::create([this]() {
		_Card->loadTextures("card/card_bg.png", "card/card_bg.png", "card/card_bg.png");
		playAnimate();
	});

	auto scaleXActionEnd = ScaleTo::create(0.5f, 0.5f, 0.5f);

	_Card->runAction(Sequence::create(
		scaleXAction,
		loadText,
		callback,
		scaleXActionEnd,
		nullptr
	));
	
}

void GameResults::playAnimate()
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("card/animate.plist");
	_spCard = Sprite::createWithSpriteFrameName("0.png");
	_spCard->setPosition(Vec2(_Card->getCustomSize() / 2) + Vec2(0, 50));
	_Card->addChild(_spCard);

	Vector<SpriteFrame*>im;
	for (int i = 0; i <6; i++) {
		im.pushBack(cache->getSpriteFrameByName(Value(i).asString() + ".png"));
	}
	Animation* animation = Animation::createWithSpriteFrames(im, 1.f / im.size());
	Animate* animate = Animate::create(animation);
	_spCard->runAction(RepeatForever::create(animate));
}
