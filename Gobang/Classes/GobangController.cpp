/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangController.cpp
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/20.
> Functional:  Gabang Controller
*******************************************************/
#include "GobangController.h"
GobangController* GobangController::instance = nullptr;
GobangController * GobangController::getInstance()
{
	if (!instance)
	{
		instance = new GobangController();
	}
	return instance;
}

void GobangController::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}	
}

bool GobangController::palyChess(ChessPieceType chessPiece, int x, int y)
{
	bool result = false;
	//The decision has been made
	if (judgeChess(x, y)) {
		
		result = false;
	}
	else {
		//Adds a piece data to the chess library
		result = true;
		ChessPiece* piece = ChessPiece::create();
		piece->setX(x);
		piece->setY(y);
		Vector<ChessPiece*>* chesses = (chessPiece == White) ? ptr_board->getWhites() : ptr_board->getBlacks();
		chesses->pushBack(piece);
	}
	if (result) {
		//Switch players after a chess
		ExchangePieces();
	}
	
	return result;
}

ChessPieceType GobangController::getChessType()
{
	return _ChessPiece;
}

bool GobangController::judgeChess(int x, int y)
{
	bool result = false;
	result=judgeChess(White, x, y);
	if(!result)
		result = judgeChess(Black, x, y);
	return result;
}

bool GobangController::judgeChess(ChessPieceType chessPiece, int x, int y)
{
	//Look for existing Gobang in the data of the two Gobang library
	bool result = false;
	if (chessPiece == White) {
		for (auto chess : *ptr_board->getWhites()) {
				if (chess->getX() == x && chess->getY() == y) {
					result = true;
					break;
				}
			}
	}
	else if (chessPiece==Black) {
				for (auto chess : *ptr_board->getBlacks()) {
					if (chess->getX() == x && chess->getY() == y) {
						result = true;
						break;
					}
				}
	}
	
	return result;
}

void GobangController::ExchangePieces()
{
	if (_ChessPiece == Black) {
		_ChessPiece = White;
	}
	else
	{
		_ChessPiece = Black;
	}
}

bool GobangController::judgeWin(ChessPieceType chessPiece, int x, int y)
{
	//The search area range is a 9x9 grid range centered on the current point
	int condition = VictoryConditions - 1;	//It's going to go up to 4 points in one direction
	int leftEdge = x - condition;
	int rightEdge = x + condition;
	int topEdge = y + condition;
	int bottomEdge = y - condition;

	//Chessboard border optimization processing, narrowing search scope.
	int length = ptr_board->getWidth();
	if (leftEdge < 0) leftEdge = 0;
	if (rightEdge > length) rightEdge = length;
	if (topEdge > length) topEdge = length;
	if (bottomEdge < 0) bottomEdge = 0;

	//Calculating the number of continuous chessmen in eight directions
	const int counter = 8;
	Vec2 dirs[counter] = {
		Vec2(0,1),
		Vec2(1,1),
		Vec2(1,0),
		Vec2(1,-1),
		Vec2(0,-1),
		Vec2(-1,-1),
		Vec2(-1,0),
		Vec2(-1,1)
	};

	std::vector<int> lengths;
	for (int i = 0; i < counter; i++)
	{
		//Record a continuous length (excluding the current drop point).
		int l = 0;
		Vec2 position = Vec2(x, y);
		while ((int)position.x >= leftEdge && (int)position.x <= rightEdge && (int)position.y <= topEdge 
			&& (int)position.y >= bottomEdge)
		{
			position += dirs[i];
			if (!judgeChess(chessPiece, (int)position.x, (int)position.y))
			{
				break;
			}
			l++;
		}

		//Record the continuous length in one direction (excluding the current drop point).
		lengths.push_back(l);
	}

	bool result = false;
	for (int i = 0; i < counter / 2; i++)
	{
		//The total length in the same direction (horizontal, vertical, positive, oblique, and four directions).
		int total = lengths[i] + lengths[i + 4] + 1;
		if (total == VictoryConditions)
		{
			result = true;
		}
	}

	return result;
}

bool GobangController::GobangTakeBack()
{
	//Return to the last chess player and withdraw the pieces.
	bool result = false;
	ExchangePieces();
	if (_ChessPiece == Black) {
		if (ptr_board->getBlacks()->size() > 0) {
			ptr_board->PopBackBlacks();
			result = true;
		}
	}
	else if (_ChessPiece == White) {
		if (ptr_board->getWhites()->size() > 0) {
			ptr_board->PopBackWhites();
			result = true;
		}
	}
	return result;
}

ChessBoard * GobangController::getChessBoard()
{
	return  ptr_board;;
}

GobangController::GobangController()
{
	_ChessPiece = Black;
	ptr_board= ChessBoard::create();
	CC_SAFE_RETAIN(ptr_board);
}

GobangController::~GobangController()
{
	CC_SAFE_DELETE(ptr_board);

}
