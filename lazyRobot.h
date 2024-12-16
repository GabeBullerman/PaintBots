#ifndef LAZYROBOT_H
#define LAZYROBOT_H

#include "IRobotAgent.h"
#include "GameBoard.h" // Include GameBoard.h for RobotMoveRequest and RobotColor

class lazyRobot : public IRobotAgent {
public:
    std::string getRobotName() override { return "lazyRobot"; }
    std::string getRobotCreator() override { return "Your Name"; }
    RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) override;
    void setRobotColor(RobotColor c) override { color = c; }

private:
    RobotColor color;
};

#endif // LAZYROBOT_H