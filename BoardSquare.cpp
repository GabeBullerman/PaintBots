// @author: Gabriel Bullerman
#include "BoardSquare.h"

// Default constructor
BoardSquare::BoardSquare()
    : squareColor(WHITE), squareType(EMPTY), redRobot(false), blueRobot(false), robotDir(NORTH) {}

// Parameterized constructor
BoardSquare::BoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir)
    : squareColor(color), squareType(type), redRobot(redRobot), blueRobot(blueRobot), robotDir(dir) {}

// Destructor
BoardSquare::~BoardSquare() {}

// Copy constructor
BoardSquare::BoardSquare(const BoardSquare& other)
    : squareColor(other.squareColor), squareType(other.squareType), redRobot(other.redRobot), blueRobot(other.blueRobot), robotDir(other.robotDir) {}

// Copy assignment operator
BoardSquare& BoardSquare::operator=(const BoardSquare& other) {
    if (this != &other) {
        squareColor = other.squareColor;
        squareType = other.squareType;
        redRobot = other.redRobot;
        blueRobot = other.blueRobot;
        robotDir = other.robotDir;
    }
    return *this;
}