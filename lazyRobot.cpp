#include "lazyRobot.h"
#include <random> // Include <random> for std::random_device and std::mt19937
#include <iostream> // Include <iostream> for std::cout

RobotMoveRequest* lazyRobot::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);

    RobotMoveRequest* move = new RobotMoveRequest();
    move->robot = color;
    move->move = RobotMove::NONE;
    move->shoot = true;
    move->direction = static_cast<Direction>(dis(gen));

    std::cout << "LazyRobot move generated: move=" << move->move << ", shoot=" << move->shoot << ", direction=" << move->direction << std::endl;

    return move;
}