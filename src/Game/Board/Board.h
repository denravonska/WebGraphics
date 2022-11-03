
#include <array>
#include <string>
#include "Piece.h"
#include "Tile.h"
#include "Point.h"
#include "Castle.h"
#include "EnPassant.h"

#ifndef BOARD_H
#define BOARD_H

class Board {
    std::array<std::array<Tile, 8>, 8> board; //board[FILE][RANK]
    void setStartPieces(PieceColor pieceColor);
    void setStartLightPieces(PieceColor pieceColor);
    void setStartHeavyPieces(PieceColor pieceColor);
    void clearTile(int file, int rank);
    void clear();

    bool isQueenSideRook(Point from, PieceColor color);
    bool isKingSideRook(Point from, PieceColor color);
    void setCastleState(Point fromMove);
    void setPassantState(Point fromMove, Point toMove);
    bool isPromoteMove(Point toMove);
    PieceType getPromoteType(int toRank);

public:
    Board();
    void reset();
    void print();

    void setPiece(int file, int rank, Piece piece);
    void movePiece(Point from, Point to);
    void castleKingSide(PieceColor color);
    void castleQueenSide(PieceColor color);

    Tile getTile(int file, int rank);
    Tile getTile(Point point);

    Castle whiteCastle, blackCastle;
    EnPassant whitePassant, blackPassant;
    
};

#endif