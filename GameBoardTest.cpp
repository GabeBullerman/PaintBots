#include "GameBoard.h"
#include "Config.h"
#include "InternalBoardSquare.h"
#include "BoardSquare.h"
#include "ExternalBoardSquare.h"
#include <cassert>
#include <iostream>

class GameBoardTest {
public:
    bool doTests() {
        return testRobotMovement() && testPaintBlobHit() && testShortRangeScan();
    }

private:
    bool testRobotMovement() {
        Config config("valid_config.cfg");
        GameBoard* board = GameBoard::getInstance("xyzzy", config);
        RobotMoveRequest moveRequest = { RobotColor::RED_ROBOT, FORWARD, false };
        assert(board->MoveRobot(moveRequest));
        std::cout << "Robot movement test passed.\n";
        return true;
    }

    bool testPaintBlobHit() {
        Config config("valid_config.cfg");
        GameBoard* board = GameBoard::getInstance("xyzzy", config);
        RobotMoveRequest moveRequest = { RobotColor::RED_ROBOT, FORWARD, true };
        assert(board->PaintBlobHit(moveRequest));
        std::cout << "Paint blob hit test passed.\n";
        return true;
    }

    bool testShortRangeScan() {
        Config config("valid_config.cfg");
        GameBoard* board = GameBoard::getInstance("xyzzy", config);
        ExternalBoardSquare** scan = board->getShortRangeScan(RobotColor::RED_ROBOT);
        assert(scan != nullptr);
        std::cout << "Short range scan test passed.\n";
        return true;
    }
};

int main() {
    GameBoardTest test;
    if (test.doTests()) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
    return 0;
}