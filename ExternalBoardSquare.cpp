// @author: Gabriel Bullerman
#include "ExternalBoardSquare.h"

// Default constructor
ExternalBoardSquare::ExternalBoardSquare()
    : BoardSquare(WHITE, EMPTY, false, false, NORTH) {}

// Constructor from InternalBoardSquare
ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare& internalSquare)
    : BoardSquare(internalSquare.getSquareColor(), internalSquare.getSquareType(), internalSquare.redRobotPresent(), internalSquare.blueRobotPresent(), internalSquare.robotDirection()) {}

// Parameterized constructor
ExternalBoardSquare::ExternalBoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir)
    : BoardSquare(color, type, redRobot, blueRobot, dir) {}