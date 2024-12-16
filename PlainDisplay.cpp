#include "PlainDisplay.h"

// Constructor: Initializes the PlainDisplay with a pointer to the GameBoard.
PlainDisplay::PlainDisplay(GameBoard* gameBoard) : gameBoard(gameBoard) {
    gameBoard->addObserver(this);
}

// update method: Called when the GameBoard notifies observers of a change.
void PlainDisplay::update() {
    display();
}

// Method to display the game board in ASCII format.
void PlainDisplay::display() const {
    for (int row = 0; row < 17; ++row) {
        for (int col = 0; col < 17; ++col) {
            const InternalBoardSquare& square = gameBoard->getSquare(row, col);
            char color = (square.getSquareColor() == RED) ? 'R' : (square.getSquareColor() == BLUE) ? 'B' : 'W';
            char robot = square.redRobotPresent() ? 'R' : square.blueRobotPresent() ? 'B' : '-';
            char rock = (square.getSquareType() == ROCK) ? 'X' : '-';
            char fog = (square.getSquareType() == FOG) ? 'X' : '-';
            if (square.getSquareType() == WALL) {
                std::cout << "WWWW";
            } else {
                std::cout << color << robot << rock << fog;
            }
        }
        std::cout << std::endl;
    }
}