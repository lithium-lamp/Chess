#include "chess.h"

Chess::Chess(const std::string& current_board_state, int move, bool finishedgame) : move_counter { move }, finishedGame { finishedgame } {
    set_board_vector(current_board_state);
}

std::string Chess::getFen() {
    std::string fenString = "";
    int counter = 0;
    int width = 1;

    for (Piece p : board_vector){
        if (width > 8) {
            if (counter != 0) {
                fenString += ("12345678")[counter - 1];
                counter = 0;
            }
            fenString += '/';
            width = 1;
        }
            

        if (p.piece_declaration != '-') {
            if (counter != 0) {
                fenString += ("12345678")[counter - 1];
                counter = 0;
            }
            fenString += p.piece_declaration;
            counter = 0;
        }
        else {
            counter++;
        }

        width++;
    } 

    return fenString;
}

bool Chess::isWhiteTurn() {
    return move_counter % 2 == 0;
}

int Chess::playMove(const std::string& userinput) { //returns result type
    if (userinput == "exit") {
        finishedGame = true;

        return -1;
    }

    std::string piecesquare = userinput.substr(0, 2);

    std::string movesquare = userinput.substr(2, 2);

    int pieceIndex = getSquareIndex(piecesquare);
    Piece piece = getPiece(pieceIndex);

    int squareIndex = getSquareIndex(movesquare);

    bool a = islower(piece.piece_declaration) != isWhiteTurn();
    bool b = isLegalMove(piece, squareIndex);

    if (a && b) {
        movePiece(piece, squareIndex);
        return 0;
    }
    else if (!a) {
        std::cout << "Wrong player attempting to make move." << std::endl;
        return 1;
    }
    else if (!b) {
        std::cout << "This is not a legal move." << std::endl;
        return 2;
    }

    return 3;
}

void Chess::movePiece(Piece piece, int squareIndex) {
    Piece movedPiece = piece;
    movedPiece.piece_index = squareIndex;

    Piece emptyPiece = piece;
    emptyPiece.piece_declaration = '-';

    board_vector[piece.piece_index] = emptyPiece;
    board_vector[squareIndex] = movedPiece;

    move_counter++;
}

int Chess::getSquareIndex(const std::string& square) {
    char horizontal_char = square[0];

    std::string possible_ver = "abcdefgh";

    int horizontal = possible_ver.find(horizontal_char) + 1;
    int vertical = (square[1] - '0');

    int board_width = 8;

    return (board_width * (board_width - vertical) + horizontal) - 1;
}

Piece Chess::getPiece(int squareIndex) {
    return board_vector[squareIndex];
}

Piece Chess::getPiece(const std::string& movesquare) {
    int squareIndex = getSquareIndex(movesquare);
    return board_vector[squareIndex];
}




bool Chess::isInCheck(const std::vector<Piece>& board) {
    Piece player_king = getPiece('K'); //if white

    std::vector<int> vecknight = knightSquares(player_king);

    std::vector<int> vecbishop = bishopSquares(player_king);

    std::vector<int> vecrook = rookSquares(player_king);

    for (int index : vecknight) {
        char c = board_vector[index].piece_declaration;

        if (c == 'n')
            return true;
    }

    for (int index : vecbishop) {
        char c = board_vector[index].piece_declaration;

        if (c == 'b' || c == 'q')
            return true;
    }

    for (int index : vecrook) {
        char c = board_vector[index].piece_declaration;

        if (c == 'r' || c == 'q')
            return true;
    }

    return false;
}

bool Chess::isLegalMove(Piece piece, int squareIndex) {
    const int err_bad_move = 0;

    char p_dec = tolower(piece.piece_declaration);

    std::vector<Piece> tempVec = board_vector;
    tempVec[piece.piece_index].piece_declaration = '-';
    tempVec[squareIndex].piece_declaration = piece.piece_declaration; //simulates the move in a temp vector

    if (isInCheck(tempVec)) {
        std::cout << "The king would be in check, therefore illegal." << std::endl;
        return false;
    }

    std::vector<int> possiblemoves;

    switch (p_dec) {
    case 'r':
        possiblemoves = rookSquares(piece);
        break;
    case 'n':
        possiblemoves = knightSquares(piece);
        break;
    case 'b':
        possiblemoves = bishopSquares(piece);
        break;
    case 'q':
        possiblemoves = queenSquares(piece);
        break;
    case 'k':
        possiblemoves = kingSquares(piece);
        break;
    case 'p':
        possiblemoves = pawnSquares(piece);
        break;
    }

    for (int possible_moves_index : possiblemoves) {
        if (possible_moves_index == squareIndex)
            return true;
    }

    return false;
}

void Chess::printBoard() {
    int board_width = 8;
    int square_hor = 1;

    for (Piece p : board_vector) {
        std::cout << " " << p.piece_declaration << " |";
        
        square_hor++;
        if (square_hor > board_width) {
            square_hor = 1;
            std::cout << std::endl;
        }
    }

    std::cout << "CURRENT MOVE: " << move_counter;
    if (isWhiteTurn())
        std::cout << ", white to play";
    else
        std::cout << ", black to play";
}

void Chess::printRefBoard() {
    std::cout << std::endl;
    std::cout << "a8 | b8 | c8 | d8 | e8 | f8 | g8 | h8 |" << std::endl;
    std::cout << "a7 | b7 | c7 | d7 | e7 | f7 | g7 | h7 |" << std::endl;
    std::cout << "a6 | b6 | c6 | d6 | e6 | f6 | g6 | h6 |" << std::endl;
    std::cout << "a5 | b5 | c5 | d5 | e5 | f5 | g5 | h5 |" << std::endl;
    std::cout << "a4 | b4 | c4 | d4 | e4 | f4 | g4 | h4 |" << std::endl;
    std::cout << "a3 | b3 | c3 | d3 | e3 | f3 | g3 | h3 |" << std::endl;
    std::cout << "a2 | b2 | c2 | d2 | e2 | f2 | g2 | h2 |" << std::endl;
    std::cout << "a1 | b1 | c1 | d1 | e1 | f1 | g1 | h1 |" << std::endl;
}

void Chess::set_board_vector(const std::string& current_board_state) {
    std::vector<Piece> piece_vector;
    Piece p;
    int vertical_numbering = 8;
    int horizontal_numbering = 1;

    int index = 0;

    for (char c : current_board_state) {
        if (c == '/') {
            vertical_numbering--;
            horizontal_numbering = 1;
            continue;
        }

        if (isdigit(c)) {
            int ic = c - '0';
            for (int i = 0; i < ic; i++) {
                p.piece_index = index;
                p.piece_declaration = '-';
                horizontal_numbering++;
                piece_vector.push_back(p);
                index++;
            }
            continue;
        }
        p.piece_index = index;
        p.piece_declaration = c;
        piece_vector.push_back(p);
        index++;
    }

    board_vector = piece_vector;
}