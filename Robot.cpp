#include "Robot.h"
#include "RobotAgentRoster.h"

Robot::Robot() : color(RobotColor::RED_ROBOT), agent(nullptr) {
    setRobotAgent(RobotAgentRoster::getInstance()->operator[]("lazyRobot"));
}

void Robot::setRobotAgent(IRobotAgent* agent) {
    this->agent = agent;
    if (agent) {
        agent->setRobotColor(color);
    }
}

IRobotAgent* Robot::getRobotAgent() const {
    return agent;
}

void Robot::setColor(RobotColor color) {
    this->color = color;
    if (agent) {
        agent->setRobotColor(color);
    }
}

RobotColor Robot::getRobotColor() const {
    return color;
}