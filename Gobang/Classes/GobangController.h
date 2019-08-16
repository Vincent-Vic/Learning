/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: GobangController.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/20.
> Functional:  Gabang Controller
*******************************************************/

#pragma once
#include "ChessBoard.h"
enum ChessPieceType{Black,White};
class GobangController
{
public:
	GobangController();
	~GobangController();
	static GobangController* getInstance();
	static void destroyInstance();
	/**
	 *effect:move in chess
	 *chessPiece:Chess type
	 *x:Position x
	 *y:Position y
	 */
	bool palyChess(ChessPieceType chessPiece,int x,int y);

	/**
	 *effect:Exchange of players
	 */
	ChessPieceType getChessType();

	/**
	*effect:The outcome to determine
	*chessPiece:Chess type
	*x:Position x
	*y:Position y
	*/
	bool judgeWin(ChessPieceType chessPiece, int x, int y);

	/**
	*effect:Realize the function of penitence
	*/
	bool GobangTakeBack();

	/**
	*effect:Get the checkerboard object
	*/
	ChessBoard* getChessBoard() ;
private:
	static GobangController* instance;
	//Records of the board
	ChessBoard* ptr_board;
	//The white chess has been recorded
	ChessPieceType _ChessPiece;

	/**
	*effect:Whether the current position is a chess piece
	*chessPiece:Chess type
	*x:Position x
	*y:Position y
	*/
	bool judgeChess(int x, int y);

	/**
	*effect:Whether the current position has a specified type of checker
	*chessPiece:Chess type
	*x:Position x
	*y:Position y
	*/
	bool judgeChess(ChessPieceType chessPiece, int x, int y);

	/**
	*effect:Exchange Pieces
	*/
	void ExchangePieces();

	/**
	*effect:Victory condition constant
	*/
	const int VictoryConditions = 5;
};