// @author: Gabriel Bullerman
#ifndef EXTERNALBOARDSQUARE_H
#define EXTERNALBOARDSQUARE_H

#include "BoardSquare.h"
#include "InternalBoardSquare.h"

class ExternalBoardSquare : public BoardSquare {
public:
    ExternalBoardSquare(); // Default constructor
    ExternalBoardSquare(const InternalBoardSquare& internalSquare); // Constructor from InternalBoardSquare
    ExternalBoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir); // Parameterized constructor
};

#endif // EXTERNALBOARDSQUARE_H