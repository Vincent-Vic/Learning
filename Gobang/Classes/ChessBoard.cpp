/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: ChessBoard.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/20.
> Functional:  Chess Board model
*******************************************************/
#include "ChessBoard.h"

bool ChessBoard::init()
{
	_width = 15;
	return true;
}

Vector<ChessPiece*>* ChessBoard::getWhites()
{
	return &prt_Whites;
}

Vector<ChessPiece*>* ChessBoard::getBlacks()
{
	return &prt_Black;
}

bool ChessBoard::PopBackWhites()
{
	if (prt_Whites.size() >= 0) {
		prt_Whites.popBack();
		return true;
	}
	return false;
}

bool ChessBoard::PopBackBlacks()
{
	if (prt_Black.size() >= 0) {
		prt_Black.popBack();
		return true;
	}
	return false;
}

int ChessBoard::getWidth()
{
	return _width;
}



