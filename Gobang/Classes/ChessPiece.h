/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: ChessPiece.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/20.
> Functional:  Chess Piece model
*******************************************************/
#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ChessPiece:public Ref
{
public:
	CREATE_FUNC(ChessPiece);
	virtual bool init();
	void setX(int x) { _x = x; }
	int getX() { return _x; }
	void setY(int y) { _y = y; }
	int getY() { return _y; }
private:
	int _x;
	int _y;
};
