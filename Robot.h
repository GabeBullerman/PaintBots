#ifndef ROBOT_H
#define ROBOT_H

#include "IRobotAgent.h"
#include "GameBoard.h" // Include GameBoard.h for RobotColor and RobotMoveRequest

class Robot {
public:
    Robot();
    void setRobotAgent(IRobotAgent* agent);
    IRobotAgent* getRobotAgent() const;
    void setColor(RobotColor color);
    RobotColor getRobotColor() const;

private:
    RobotColor color;
    IRobotAgent* agent;
};

#endif // ROBOT_H