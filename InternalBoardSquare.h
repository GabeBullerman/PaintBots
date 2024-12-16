// @author: Gabriel Bullerman
#ifndef INTERNALBOARDSQUARE_H
#define INTERNALBOARDSQUARE_H

#include "BoardSquare.h"

class InternalBoardSquare : public BoardSquare {
public:
    // Default constructor: Initializes an empty InternalBoardSquare.
    InternalBoardSquare();

    // Parameterized constructor: Initializes an InternalBoardSquare with the specified properties.
    InternalBoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir);

    // Sets the type of the square (e.g., EMPTY, ROCK, FOG, WALL).
    void setSquareType(SquareType type);

    // Sets whether the red robot is present on the square.
    void setRedRobotPresent(bool present);

    // Sets whether the blue robot is present on the square.
    void setBlueRobotPresent(bool present);

    // Sets the color of the square (e.g., RED, BLUE, WHITE).
    void setSquareColor(Color color);

    // Sets the direction the robot is facing on the square (e.g., NORTH, SOUTH, EAST, WEST).
    void setRobotDirection(Direction dir);
};

#endif // INTERNALBOARDSQUARE_H