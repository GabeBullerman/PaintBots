// @author: Gabriel Bullerman
#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

// Enumerations for direction, square type, and color.
enum Direction { NORTH, SOUTH, EAST, WEST };
enum SquareType { EMPTY, ROCK, FOG, WALL };
enum Color { RED, BLUE, WHITE };

class BoardSquare {
public:
    BoardSquare(); // Default constructor
    BoardSquare(Color color, SquareType type, bool redRobot, bool blueRobot, Direction dir); // Parameterized constructor
    virtual ~BoardSquare(); // Destructor
    BoardSquare(const BoardSquare& other); // Copy constructor
    BoardSquare& operator=(const BoardSquare& other); // Copy assignment operator

    // Getter methods
    inline Color getSquareColor() const { return squareColor; }
    inline SquareType getSquareType() const { return squareType; }
    inline bool redRobotPresent() const { return redRobot; }
    inline bool blueRobotPresent() const { return blueRobot; }
    inline Direction robotDirection() const { return robotDir; }

protected:
    Color squareColor;
    SquareType squareType;
    bool redRobot;
    bool blueRobot;
    Direction robotDir;
};

#endif // BOARDSQUARE_H