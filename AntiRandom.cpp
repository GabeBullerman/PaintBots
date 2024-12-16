#include "AntiRandom.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <cmath>

AntiRandom::AntiRandom() {
    std::srand(std::time(0)); // Seed for random number generation
    obstaclesMemorized = false;
    currentRow = currentCol = 0;
    turnCounter = 0;
    initializeMapEdges();
    initializeMemoryGrid();
}

RobotMoveRequest* AntiRandom::getMove(ExternalBoardSquare** srs, ExternalBoardSquare** lrs) {
    RobotMoveRequest* move = new RobotMoveRequest();
    move->robot = color;
    move->shoot = false;

    if (!obstaclesMemorized) {
        memorizeObstacles(lrs);
        obstaclesMemorized = true;
        planPathToTargets();
    }

    // Perform a long-range scan every 6th turn
    if (turnCounter % 6 == 0 && turnCounter / 6 < 26) {
        updateMapWithLongRangeScan(lrs);
    }
    turnCounter++;

    // Update memory grid with short-range scan
    updateMemoryGridWithShortRangeScan(srs);

    Direction currentDirection = srs[2][2].robotDirection();

    // Check if the opponent is in range and shoot if possible
    if (isOpponentInRange(srs)) {
        move->shoot = true;
        move->direction = currentDirection;
    }

    // Determine the best move to make
    if (isInCorner(srs)) {
        move->move = handleCornerMovement(srs, currentDirection);
    } else if (isObstacleAhead(srs, currentDirection) || isVisitedTooOften(currentRow, currentCol, currentDirection)) {
        move->move = findAlternativeMove(srs, currentDirection);
    } else if (hasNotMovedInTurns(3)) {
        Direction openDirection = findOpenDirection(srs);
        if (openDirection == currentDirection) {
            move->move = FORWARD;
        } else if (openDirection == rotateLeftDirection(currentDirection)) {
            move->move = ROTATELEFT;
        } else {
            move->move = ROTATERIGHT;
        }
    } else {
        move->move = FORWARD;
    }

    updateLastMoves(move->move);
    updateVisited(currentRow, currentCol, currentDirection, move->move);
    updateCurrentPosition(currentDirection, move->move);
    return move;
}

void AntiRandom::setRobotColor(RobotColor color) {
    this->color = color;
}

bool AntiRandom::isObstacleAhead(ExternalBoardSquare** srs, Direction direction) {
    int row = 2, col = 2;

    switch (direction) {
        case NORTH: row -= 1; break;
        case EAST: col += 1; break;
        case SOUTH: row += 1; break;
        case WEST: col -= 1; break;
    }

    return srs[row][col].getSquareType() == SquareType::ROCK || srs[row][col].getSquareType() == SquareType::WALL ||
           srs[row][col].getSquareType() == SquareType::FOG || srs[row][col].redRobotPresent() || srs[row][col].blueRobotPresent();
}

Direction AntiRandom::rotateLeftDirection(Direction currentDirection) {
    switch (currentDirection) {
        case NORTH: return WEST;
        case WEST: return SOUTH;
        case SOUTH: return EAST;
        case EAST: return NORTH;
    }
    return NORTH; // Default case
}

Direction AntiRandom::rotateRightDirection(Direction currentDirection) {
    switch (currentDirection) {
        case NORTH: return EAST;
        case EAST: return SOUTH;
        case SOUTH: return WEST;
        case WEST: return NORTH;
    }
    return NORTH; // Default case
}

Direction AntiRandom::findOpenDirection(ExternalBoardSquare** srs) {
    std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};
    std::random_shuffle(directions.begin(), directions.end());

    for (Direction dir : directions) {
        if (!isObstacleAhead(srs, dir) && !isVisitedTooOften(currentRow, currentCol, dir)) {
            return dir;
        }
    }
    return NORTH; // Default case
}

Direction AntiRandom::findBestDirection(ExternalBoardSquare** srs, Direction currentDirection) {
    if (!isObstacleAhead(srs, currentDirection) && !isVisitedTooOften(currentRow, currentCol, currentDirection)) {
        return currentDirection;
    }
    Direction left = rotateLeftDirection(currentDirection);
    Direction right = rotateRightDirection(currentDirection);
    if (!isObstacleAhead(srs, left) && !isVisitedTooOften(currentRow, currentCol, left)) {
        return left;
    }
    if (!isObstacleAhead(srs, right) && !isVisitedTooOften(currentRow, currentCol, right)) {
        return right;
    }
    return findOpenDirection(srs);
}

int AntiRandom::evaluateDirection(ExternalBoardSquare** srs, Direction direction) {
    int row = 2, col = 2;

    switch (direction) {
        case NORTH: row -= 1; break;
        case EAST: col += 1; break;
        case SOUTH: row += 1; break;
        case WEST: col -= 1; break;
    }

    if (srs[row][col].getSquareType() == SquareType::ROCK || srs[row][col].getSquareType() == SquareType::WALL ||
        srs[row][col].getSquareType() == SquareType::FOG) {
        return -1;
    }
    if (srs[row][col].redRobotPresent() || srs[row][col].blueRobotPresent()) {
        return -1;
    }
    return 1;
}

bool AntiRandom::isInCorner(ExternalBoardSquare** srs) {
    int row = 2, col = 2;
    return (srs[row - 1][col].getSquareType() == SquareType::WALL || srs[row + 1][col].getSquareType() == SquareType::WALL) &&
           (srs[row][col - 1].getSquareType() == SquareType::WALL || srs[row][col + 1].getSquareType() == SquareType::WALL);
}

RobotMove AntiRandom::handleCornerMovement(ExternalBoardSquare** srs, Direction currentDirection) {
    Direction bestDirection = findBestDirection(srs, currentDirection);
    if (bestDirection == currentDirection) {
        return FORWARD;
    }
    if (bestDirection == rotateLeftDirection(currentDirection)) {
        return ROTATELEFT;
    }
    return ROTATERIGHT;
}

bool AntiRandom::isRepeatingMoves() {
    if (lastMoves.size() < 4) {
        return false;
    }
    return lastMoves[0] == lastMoves[2] && lastMoves[1] == lastMoves[3];
}

RobotMove AntiRandom::findAlternativeMove(ExternalBoardSquare** srs, Direction currentDirection) {
    if (isRepeatingMoves()) {
        return ROTATERIGHT;
    }
    return ROTATELEFT;
}

void AntiRandom::updateLastMoves(RobotMove move) {
    if (lastMoves.size() >= 4) {
        lastMoves.pop_front();
    }
    lastMoves.push_back(move);
}

bool AntiRandom::isOpponentInRange(ExternalBoardSquare** srs) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if ((srs[i][j].redRobotPresent() && color == RobotColor::BLUE_ROBOT) ||
                (srs[i][j].blueRobotPresent() && color == RobotColor::RED_ROBOT)) {
                return true;
            }
        }
    }
    return false;
}

void AntiRandom::memorizeObstacles(ExternalBoardSquare** lrs) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (lrs[i][j].getSquareType() == SquareType::ROCK) {
                obstacles.push_back({i, j});
            } else if (lrs[i][j].getSquareType() == SquareType::WALL) {
                walls.push_back({i, j});
            } else if (lrs[i][j].getSquareType() == SquareType::FOG) {
                fog.push_back({i, j});
            } else if (lrs[i][j].getSquareType() == SquareType::EMPTY || lrs[i][j].getSquareColor() == Color::BLUE) {
                targets.push_back({i, j});
            }
        }
    }
}

void AntiRandom::updateMapWithLongRangeScan(ExternalBoardSquare** lrs) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (lrs[i][j].getSquareType() == SquareType::ROCK && !isObstacleAt(i, j)) {
                obstacles.push_back({i, j});
            } else if (lrs[i][j].getSquareType() == SquareType::WALL && !isObstacleAt(i, j)) {
                walls.push_back({i, j});
            } else if (lrs[i][j].getSquareType() == SquareType::FOG && !isObstacleAt(i, j)) {
                fog.push_back({i, j});
            } else if ((lrs[i][j].getSquareType() == SquareType::EMPTY || lrs[i][j].getSquareColor() == Color::BLUE) && !isObstacleAt(i, j)) {
                targets.push_back({i, j});
            }
            memoryGrid[i][j].type = static_cast<MemorySquareType>(lrs[i][j].getSquareType());
            memoryGrid[i][j].redRobotPresent = lrs[i][j].redRobotPresent();
            memoryGrid[i][j].blueRobotPresent = lrs[i][j].blueRobotPresent();
        }
    }
}

bool AntiRandom::isObstacleAt(int row, int col) {
    for (const auto& obstacle : obstacles) {
        if (obstacle.first == row && obstacle.second == col) {
            return true;
        }
    }
    for (const auto& wall : walls) {
        if (wall.first == row && wall.second == col) {
            return true;
        }
    }
    for (const auto& fog : fog) {
        if (fog.first == row && fog.second == col) {
            return true;
        }
    }
    return false;
}

void AntiRandom::planPathToTargets() {
    // Sort targets based on distance from the current position
    std::sort(targets.begin(), targets.end(), [this](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return std::hypot(a.first - currentRow, a.second - currentCol) < std::hypot(b.first - currentRow, b.second - currentCol);
    });
}

std::pair<int, int> AntiRandom::findNextTarget() {
    if (!targets.empty()) {
        std::pair<int, int> nextTarget = targets.front();
        targets.erase(targets.begin());
        return nextTarget;
    }
    return {currentRow, currentCol}; // No more targets, stay in place
}

void AntiRandom::initializeMapEdges() {
    for (int i = 0; i < 15; ++i) {
        walls.push_back({0, i});
        walls.push_back({14, i});
        walls.push_back({i, 0});
        walls.push_back({i, 14});
    }
}

void AntiRandom::initializeMemoryGrid() {
    memoryGrid.resize(17, std::vector<MemorySquare>(17));
    for (int i = 0; i < 17; ++i) {
        memoryGrid[0][i].type = WALL;
        memoryGrid[16][i].type = WALL;
        memoryGrid[i][0].type = WALL;
        memoryGrid[i][16].type = WALL;
    }
}

void AntiRandom::updateMemoryGridWithShortRangeScan(ExternalBoardSquare** srs) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int row = currentRow - 2 + i;
            int col = currentCol - 2 + j;
            if (row >= 0 && row < 17 && col >= 0 && col < 17) {
                memoryGrid[row][col].type = static_cast<MemorySquareType>(srs[i][j].getSquareType());
                memoryGrid[row][col].redRobotPresent = srs[i][j].redRobotPresent();
                memoryGrid[row][col].blueRobotPresent = srs[i][j].blueRobotPresent();
            }
        }
    }
}

void AntiRandom::updateVisited(int row, int col, Direction direction, RobotMove move) {
    std::pair<int, int> newPosition = {row, col};
    switch (move) {
        case FORWARD:
            if (direction == NORTH) newPosition.first--;
            else if (direction == SOUTH) newPosition.first++;
            else if (direction == EAST) newPosition.second++;
            else if (direction == WEST) newPosition.second--;
            break;
        case BACKWARD:
            if (direction == NORTH) newPosition.first++;
            else if (direction == SOUTH) newPosition.first--;
            else if (direction == EAST) newPosition.second--;
            else if (direction == WEST) newPosition.second++;
            break;
        default:
            break;
    }
    visited[newPosition]++;
}

bool AntiRandom::isVisitedTooOften(int row, int col, Direction direction) {
    std::pair<int, int> newPosition = {row, col};
    switch (direction) {
        case NORTH: newPosition.first--; break;
        case SOUTH: newPosition.first++; break;
        case EAST: newPosition.second++; break;
        case WEST: newPosition.second--; break;
    }
    return visited[newPosition] >= 2; // Lower the threshold to heavily punish revisiting spaces
}

bool AntiRandom::hasNotMovedInTurns(int turns) {
    if (lastMoves.size() < turns) {
        return false;
    }
    for (int i = 0; i < turns; ++i) {
        if (lastMoves[lastMoves.size() - 1 - i] != NONE) {
            return false;
        }
    }
    return true;
}

void AntiRandom::updateCurrentPosition(Direction direction, RobotMove move) {
    switch (move) {
        case FORWARD:
            if (direction == NORTH) currentRow--;
            else if (direction == SOUTH) currentRow++;
            else if (direction == EAST) currentCol++;
            else if (direction == WEST) currentCol--;
            break;
        case BACKWARD:
            if (direction == NORTH) currentRow++;
            else if (direction == SOUTH) currentRow--;
            else if (direction == EAST) currentCol--;
            else if (direction == WEST) currentCol++;
            break;
        default:
            break;
    }
}