#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <string>
#include "GameBoard.h"
#include "Robot.h"

class GameLogic {
public:
    GameLogic();
    void playGame(const std::string& boardconfig, const std::string& robotconfig);
    void setPause(bool pausemode);

private:
    bool pause;
    void pauseGame() const;
};

#endif // GAMELOGIC_H