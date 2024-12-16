#ifndef IROBOTAGENT_H
#define IROBOTAGENT_H

#include <string>
#include "ExternalBoardSquare.h"
#include "GameBoard.h" // Include GameBoard.h for RobotColor and RobotMoveRequest

class IRobotAgent {
public:
    virtual std::string getRobotName() = 0;
    virtual std::string getRobotCreator() = 0;
    virtual RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) = 0;
    virtual void setRobotColor(RobotColor c) = 0;
};

#endif // IROBOTAGENT_H