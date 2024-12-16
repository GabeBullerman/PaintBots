#ifndef ANTI_RANDOM_H
#define ANTI_RANDOM_H

#include "IRobotAgent.h"
#include "GameBoard.h" // Include GameBoard.h for RobotMoveRequest and RobotColor
#include <deque>
#include <vector>
#include <utility>
#include <map>

class AntiRandom : public IRobotAgent {
public:
    AntiRandom();
    std::string getRobotName() override { return "BeatRandom"; }
    std::string getRobotCreator() override { return "Gabe Bullerman"; }
    RobotMoveRequest* getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) override;
    void setRobotColor(RobotColor color) override;

private:
    enum MemorySquareType {
        EMPTY,
        WALL,
        ROCK,
        FOG,
        BLUE,
        RED
    };

    struct MemorySquare {
        MemorySquareType type;
        bool redRobotPresent;
        bool blueRobotPresent;

        MemorySquare() : type(EMPTY), redRobotPresent(false), blueRobotPresent(false) {}
    };

    RobotColor color;
    std::deque<RobotMove> lastMoves;
    std::vector<std::pair<int, int>> obstacles;
    std::vector<std::pair<int, int>> walls;
    std::vector<std::pair<int, int>> fog;
    std::vector<std::pair<int, int>> targets;
    bool obstaclesMemorized;
    int currentRow, currentCol;
    int turnCounter;
    std::map<std::pair<int, int>, int> visited; // Changed to int to count visits
    std::vector<std::vector<MemorySquare>> memoryGrid; // Memory grid for the robot

    bool isObstacleAhead(ExternalBoardSquare** srs, Direction direction);
    Direction rotateLeftDirection(Direction currentDirection);
    Direction rotateRightDirection(Direction currentDirection);
    Direction findOpenDirection(ExternalBoardSquare** srs);
    Direction findBestDirection(ExternalBoardSquare** srs, Direction currentDirection);
    int evaluateDirection(ExternalBoardSquare** srs, Direction direction);
    bool isInCorner(ExternalBoardSquare** srs);
    RobotMove handleCornerMovement(ExternalBoardSquare** srs, Direction currentDirection);
    bool isRepeatingMoves();
    RobotMove findAlternativeMove(ExternalBoardSquare** srs, Direction currentDirection);
    void updateLastMoves(RobotMove move);
    bool isOpponentInRange(ExternalBoardSquare** srs);
    void memorizeObstacles(ExternalBoardSquare** lrs);
    void updateMapWithLongRangeScan(ExternalBoardSquare** lrs);
    bool isObstacleAt(int row, int col);
    void planPathToTargets();
    std::pair<int, int> findNextTarget();
    void initializeMapEdges();
    void initializeMemoryGrid();
    void updateMemoryGridWithShortRangeScan(ExternalBoardSquare** srs);
    void updateVisited(int row, int col, Direction direction, RobotMove move);
    bool isVisitedTooOften(int row, int col, Direction direction);
    bool hasNotMovedInTurns(int turns);
    void updateCurrentPosition(Direction direction, RobotMove move);
};

#endif // ANTI_RANDOM_H