/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: ChessBoard.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/20.
> Functional:  Chess Board model
*******************************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ChessPiece.h"

class ChessBoard :public Ref
{
public:
	CREATE_FUNC(ChessBoard);
	virtual bool init();
	Vector<ChessPiece*>* getWhites();
	Vector<ChessPiece*>* getBlacks();
	bool PopBackWhites();
	bool PopBackBlacks();
	int getWidth();
	
private:
	int _width;
	//The white chess has been recorded
	Vector<ChessPiece*> prt_Whites;
	//The black chess has been recorded
	Vector<ChessPiece*> prt_Black;
};