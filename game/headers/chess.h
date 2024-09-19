///
/// \file chess.h
///

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

struct Piece {
	char piece_declaration; //char for piece, ex 'p' for pawn
	int piece_index; //location of piece on board_vector
	int passant_dir; //0, no passant. -1 left. 1 right.
};

class Chess {
public:
	Chess(const std::string& current_board_state);
	
	void printBoard();

	void printRefBoard();

	void set_board_vector(const std::string& current_board_state);

	void playMove();

	bool isInCheck(const std::vector<Piece>& board);

	bool isLegalMove(Piece piece, int squareIndex);

	int getSquareIndex(const std::string& square);

	Piece getPiece(int squareIndex);

	Piece getPiece(const std::string& movesquare);

	void movePiece(Piece piece, int squareIndex);

	std::string getFen();

	bool isWhiteTurn();

	std::vector<Piece> board_vector;


	Piece getPiece(char p_dec);

	std::vector<int> rookSquares(Piece rook);

	std::vector<int> knightSquares(Piece knight);

	std::vector<int> bishopSquares(Piece bishop);

	std::vector<int> queenSquares(Piece queen);

	std::vector<int> kingSquares(Piece king);

	std::vector<int> pawnSquares(Piece pawn);


	std::vector<int> getDir(Piece piece, int change_value, bool repeating);
	int move_counter;
};