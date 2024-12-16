// @author: Gabriel Bullerman
#ifndef PLAINDISPLAY_H
#define PLAINDISPLAY_H

#include "ObserverPattern.h"
#include "GameBoard.h"
#include <iostream>

class PlainDisplay : public Observer {
public:
    // Constructor: Initializes the PlainDisplay with a pointer to the GameBoard.
    PlainDisplay(GameBoard* gameBoard);

    // update method: Called when the GameBoard notifies observers of a change.
    void update() override;

    // display method: Outputs the current state of the GameBoard in ASCII format.
    void display() const;

private:
    GameBoard* gameBoard; // Pointer to the GameBoard being observed.
};

#endif // PLAINDISPLAY_H