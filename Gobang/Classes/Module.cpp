/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: Module.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/18.
> Functional:  Material element
*******************************************************/
#include "Module.h"
Module* Module::Instance = nullptr;
Module * Module::getInstance()
{
	if (!Instance)
	{
		Instance = new Module();
	}
	return Instance;
}

void Module::destroyInstance()
{
	if (Instance != nullptr) {
		delete Instance;
		Instance = nullptr;
	}
}

Sprite * Module::createMaterial(String address,  Vec2 vec)
{
	Size visiable = Director::getInstance()->getVisibleSize();
	Sprite* HomeMaterial = Sprite::create(address.getCString());
	ResErrHandling(!HomeMaterial, "0xPB0000XX");
	if (!HomeMaterial)
		return nullptr;
	HomeMaterial->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	HomeMaterial->setContentSize(visiable);
	HomeMaterial->setPosition(vec);
	return HomeMaterial;
}

CheckBox * Module::createCheckBox(bool seleced, Vec2 vec)
{
	CheckBox* checkBox = CheckBox::create();
	ResErrHandling(!checkBox, "0xPB300003");
	if (!checkBox)
		return nullptr;
	//����
	checkBox->setPosition(vec);
	checkBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	checkBox->setScale(0.5f);
	//���ñ���
	checkBox->loadTextureBackGround("Button/CheckBox.png");
	checkBox->loadTextureBackGroundSelected("Button/CheckBox_Press.png");

	//���ù�ѡ��
	checkBox->loadTextureFrontCross("Button/CheckBox_Select.png");
	//��ѡĬ��
	checkBox->setSelectedState(seleced);
	return checkBox;
}

RadioButton * Module::createRadioButton(Vec2 vec, int id)
{
	auto Radio = RadioButton::create();
	if (!Radio)
		return nullptr;
	ResErrHandling(!Radio, "0xPB300005");
	Radio->setPosition(vec);
	Radio->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Radio->setScale(0.05f);
	Radio->loadTextureBackGround("Button/Radio.png");
	Radio->loadTextureFrontCross("Button/Radio_Select.png"); 
	Radio->loadTextureBackGroundDisabled("Button/Radio_Disabled.png");
	Radio->loadTextureFrontCrossDisabled("Button/Radio_Select_Disabled.png");
	Radio->setTag(id);
	if (Radio->getTag() == (int)GobangData::getInstance()->getGameTime()) {
		Radio->setSelected(true);
	}
	return Radio;
}

Label * Module::createLabel(String name, Vec2 vec)
{
	Label* label = Label::create(name.getCString(), "����", 10);
	ResErrHandling(!label, "0xPB300004");
	if (!label)
		return nullptr;
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	label->setColor(Color3B::BLACK);
	label->setPosition(vec);

	return label;
}

Button * Module::createCloseButton(Vec2 vec, float scale)
{
	auto Close = Button::create("Button/close.png", "Button/close_Press.png");
	ResErrHandling(!Close, "0xPBB000UX");
	if (!Close)
		return nullptr;
	Close->setScale(scale);
	Close->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	Close->setPosition(vec);
	return Close;
}

Button * Module::createControlButton(String normal, String press, Vec2 vec, float scale)
{
	auto ControlButton = Button::create(normal.getCString(), press.getCString());
	ResErrHandling(!ControlButton, "0xPBX000CB");
	if (!ControlButton)
		return nullptr;
	ControlButton->setScale(scale);
	ControlButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	ControlButton->setPosition(vec);
	return ControlButton;
}

std::string Module::getCNByID(int id)
{
	//�������Ϊ�գ�ȥ��ȡ�����ļ�����Ϊ�ղ���Ҫ��ȡ
	if (prt_cnWords.empty())
	{
		//��ȡ������plist�����ļ�
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();
			Value val = mapPair.second;

			prt_cnWords.insert(std::pair<int, Value>(key, val));
		}
	}

	if (prt_cnWords.empty())
	{
		return "";
	}

	return prt_cnWords.at(id).asString();
}