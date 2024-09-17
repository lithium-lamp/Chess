#include "game/headers/chess.h"

std::vector<int> Chess::rookSquares(Piece rook) {
	std::vector<int> all_indexes {-8, -1, 1, 8};

	std::vector<int> available_squares;

	std::vector<int> tempVec;
	for (int curr_index : all_indexes) {
		tempVec = getDir(rook, curr_index, true);

		available_squares.insert(available_squares.begin(), tempVec.begin(), tempVec.end());
	}

	return available_squares;
}

std::vector<int> Chess::knightSquares(Piece knight) {
	std::vector<int> all_indexes{ -17, -15, -10, -6, 6, 10, 15, 17 };

	std::vector<int> available_squares;

	std::vector<int> tempVec;
	for (int curr_index : all_indexes) {
		tempVec = getDir(knight, curr_index, false);

		available_squares.insert(available_squares.begin(), tempVec.begin(), tempVec.end());
	}

	return available_squares;
}

std::vector<int> Chess::bishopSquares(Piece bishop) {
	std::vector<int> all_indexes{-9, -7, 7, 9};

	std::vector<int> available_squares;

	std::vector<int> tempVec;
	for (int curr_index : all_indexes) {
		tempVec = getDir(bishop, curr_index, true);
		available_squares.insert(available_squares.begin(), tempVec.begin(), tempVec.end());
	}

	return available_squares;
}

std::vector<int> Chess::queenSquares(Piece queen) {
	std::vector<int> all_indexes_bishop{ -9, -7, 7, 9 };

	std::vector<int> available_squares;

	std::vector<int> tempVec_bishop;
	for (int curr_index : all_indexes_bishop) {
		tempVec_bishop = getDir(queen, curr_index, true);
		available_squares.insert(available_squares.begin(), tempVec_bishop.begin(), tempVec_bishop.end());
	}

	std::vector<int> all_indexes_rook { -8, -1, 1, 8 };

	std::vector<int> tempVec_rook;
	for (int curr_index : all_indexes_rook) {
		tempVec_rook = getDir(queen, curr_index, true);

		available_squares.insert(available_squares.begin(), tempVec_rook.begin(), tempVec_rook.end());
	}

	return available_squares;
}

std::vector<int> Chess::kingSquares(Piece king) {
	std::vector<int> all_indexes{ -9, -8, -7, -1, 1, 7, 8, 9 };

	std::vector<int> available_squares;

	std::vector<int> tempVec;
	for (int curr_index : all_indexes) {
		tempVec = getDir(king, curr_index, false);
		available_squares.insert(available_squares.begin(), tempVec.begin(), tempVec.end());
	}

	return available_squares;
}

std::vector<int> Chess::pawnSquares(Piece pawn) {
	std::vector<int> all_indexes;

	if (islower(pawn.piece_declaration)) { //black pieces
		all_indexes.push_back(8);

		if (pawn.piece_index >= 8 && pawn.piece_index <= 15) {
			all_indexes.push_back(16);
		}

		if (!islower(board_vector[pawn.piece_index + 7].piece_declaration))
			all_indexes.push_back(7);

		if (!islower(board_vector[pawn.piece_index + 9].piece_declaration))
			all_indexes.push_back(9);
		
		if (pawn.passant_dir != 0 && pawn.piece_index >= 40 && pawn.piece_index <= 47) {
			all_indexes.push_back(8 + pawn.passant_dir);
		}
	}
	else { //white pieces
		all_indexes.push_back(-8);

		if (pawn.piece_index >= 48 && pawn.piece_index <= 55) {
			all_indexes.push_back(-16);
		}

		if (islower(board_vector[pawn.piece_index - 7].piece_declaration))
			all_indexes.push_back(-7);

		if (islower(board_vector[pawn.piece_index - 9].piece_declaration))
			all_indexes.push_back(-9);

		if (pawn.passant_dir != 0 && pawn.piece_index >= 24 && pawn.piece_index <= 31) {
			all_indexes.push_back(-8 + pawn.passant_dir);
		}
	}

	std::vector<int> available_squares;

	std::vector<int> tempVec;
	for (int curr_index : all_indexes) {
		tempVec = getDir(pawn, curr_index, false);

		available_squares.insert(available_squares.begin(), tempVec.begin(), tempVec.end());
	}

	return available_squares;
}

Piece Chess::getPiece(char p_dec) {
	Piece tempp;

	tempp.passant_dir = 0;
	tempp.piece_declaration = 't'; //returns 't' piece if not found
	tempp.piece_index = 0;

	for (Piece p : board_vector) { //for white
		if (p.piece_declaration == p_dec) //large K for white player
			tempp = p;
	}

	return tempp;
}





std::vector<int> Chess::getDir(Piece piece, int change_value, bool repeating) {
	int curr_index = piece.piece_index + change_value;
	
	std::vector<int> tempvec;
	
	do {
		if (curr_index >= 0 && curr_index <= 63) {
			char c = board_vector[curr_index].piece_declaration;

			if (c == '-') {//empty square, this is legal
				tempvec.push_back(curr_index);
				curr_index += change_value;
			}
			else if (!islower(piece.piece_declaration)) { //CHECK IF WHITE PIECE
				if (islower(c)) { //if a black piece, stop code
					tempvec.push_back(curr_index);
					return tempvec;
				}
				else { //is a white piece, stop code
					return tempvec;
				}
			}
			else { //IS BLACK PIECE
				if (!islower(c)) { //if a white piece, stop code
					tempvec.push_back(curr_index);
					return tempvec;
				}
				else { //is a black piece, stop code
					return tempvec;
				}
			}
		}
	}
	while (repeating && curr_index >= 0 && curr_index <= 63);

	return tempvec;
}