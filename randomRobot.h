#ifndef RANDOMROBOT_H
#define RANDOMROBOT_H

#include "IRobotAgent.h"
#include "GameBoard.h" // Include GameBoard.h for RobotMoveRequest and RobotColor

class RandomRobot : public IRobotAgent {
public:
    RandomRobot(); // Constructor declaration
    std::string getRobotName() override { return "randomRobot"; }
    std::string getRobotCreator() override { return "Gabe Bullerman"; }
    RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) override;
    void setRobotColor(RobotColor c) override;

private:
    RobotColor color;
    bool isObstacleAhead(ExternalBoardSquare** srs, Direction direction);
};

#endif // RANDOMROBOT_H