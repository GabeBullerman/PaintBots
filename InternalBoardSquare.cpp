// @author: Gabriel Bullerman
#include "InternalBoardSquare.h"

// Default constructor: Initializes an empty InternalBoardSquare.
InternalBoardSquare::InternalBoardSquare()
    : BoardSquare() {}

// Parameterized constructor: Initializes an InternalBoardSquare with the specified properties.
InternalBoardSquare::InternalBoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir)
    : BoardSquare(color, type, redRobot, blueRobot, dir) {}

// Sets the type of the square (e.g., EMPTY, ROCK, FOG, WALL).
void InternalBoardSquare::setSquareType(SquareType type) {
    squareType = type;
}

// Sets whether the red robot is present on the square.
void InternalBoardSquare::setRedRobotPresent(bool present) {
    redRobot = present;
}

// Sets whether the blue robot is present on the square.
void InternalBoardSquare::setBlueRobotPresent(bool present) {
    blueRobot = present;
}

// Sets the color of the square (e.g., RED, BLUE, WHITE).
void InternalBoardSquare::setSquareColor(Color color) {
    squareColor = color;
}

// Sets the direction the robot is facing on the square (e.g., NORTH, SOUTH, EAST, WEST).
void InternalBoardSquare::setRobotDirection(Direction dir) {
    robotDir = dir;
}