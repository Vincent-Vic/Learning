/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: Module.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/18.
> Functional:  Material element
*******************************************************/
#pragma once
#include "cocos2d.h"

USING_NS_CC;

#include"ui/CocosGUI.h"
using namespace ui;

#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;
#include "Error.h"
#include "GobangData.h"

class Module
{
public:

	static Module* getInstance(); 
	static void  destroyInstance();
	Sprite* createMaterial(String address, Vec2 vec=Vec2(0,0));
	CheckBox * createCheckBox(bool seleced, Vec2 vec);
	RadioButton * createRadioButton(Vec2 vec, int id=0);
	Label * createLabel(String name, Vec2 vec );
	Button* createCloseButton(Vec2 vec, float scale = 0.5f);
	Button* createControlButton(String normal, String press, Vec2 vec, float scale = 0.5f);
	std::string getCNByID(int id);
private:
	Module() {}
	~Module() {}
	static Module * Instance;
	//Record text table (cache data)
	std::map<int, Value> prt_cnWords;
};