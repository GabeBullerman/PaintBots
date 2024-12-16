#include "randomRobot.h"
#include <cstdlib>
#include <ctime>

RandomRobot::RandomRobot() {
    std::srand(std::time(0)); // Seed for random number generation
}

RobotMoveRequest* RandomRobot::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) {
    RobotMoveRequest* move = new RobotMoveRequest();
    move->robot = color;
    move->shoot = false;

    // Determine the robot's current direction
    Direction currentDirection = srs[2][2].robotDirection();

    // Randomly decide to move forward or rotate
    int action = std::rand() % 3; // 0: FORWARD, 1: ROTATELEFT, 2: ROTATERIGHT

    if (action == 0 && !isObstacleAhead(srs, currentDirection)) {
        move->move = FORWARD;
    } else if (action == 1) {
        move->move = ROTATELEFT;
    } else {
        move->move = ROTATERIGHT;
    }

    return move;
}

void RandomRobot::setRobotColor(RobotColor color) {
    this->color = color;
}

bool RandomRobot::isObstacleAhead(ExternalBoardSquare** srs, Direction direction) {
    int row = 2, col = 2; // Robot's current position in the center of the scan

    // Determine the square directly ahead based on the current direction
    switch (direction) {
        case NORTH:
            row -= 1;
            break;
        case EAST:
            col += 1;
            break;
        case SOUTH:
            row += 1;
            break;
        case WEST:
            col -= 1;
            break;
    }

    // Check if the move will result in hitting an obstacle (wall, rock, or another robot)
    if (srs[row][col].getSquareType() == SquareType::WALL ||
        srs[row][col].getSquareType() == SquareType::ROCK ||
        srs[row][col].redRobotPresent() || srs[row][col].blueRobotPresent()) {
        return true;
    }
    return false;
}