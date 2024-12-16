#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "Config.h"
#include "ObserverPattern.h" // Include the observer pattern header
#include <vector>

enum class RobotColor { RED_ROBOT, BLUE_ROBOT };
enum RobotMove { ROTATELEFT, ROTATERIGHT, FORWARD, BACKWARD, NONE };

struct RobotMoveRequest {
    RobotColor robot;
    RobotMove move;
    bool shoot;
    Direction direction;
};

class GameBoard : public Observable { // Inherit from Observable
public:
    static GameBoard* getInstance(const std::string& password);
    static GameBoard* getInstance(const std::string& password, const Config& config);
    InternalBoardSquare& getSquare(int row, int col);
    bool MoveRobot(const RobotMoveRequest& mr);
    bool PaintBlobHit(const RobotMoveRequest& mr);
    int blueScore() const;
    int redScore() const;
    void setSquareColor(int row, int col, Color c);
    void setRobotPaintColor(RobotColor robot, Color sc);
    ExternalBoardSquare** getLongRangeScan();
    ExternalBoardSquare** getShortRangeScan(RobotColor rc);
    bool checkRobotCollision(RobotColor movingRobot); // Add this line

private:
    GameBoard();
    GameBoard(const Config& config);
    void initializeBoard(const Config& config);
    void placeRocksAndFog(const Config& config);
    void placeRobots();
    static GameBoard* instance;
    std::vector<std::vector<InternalBoardSquare>> board;
    int redHitDuration;
    int blueHitDuration;
};

#endif // GAMEBOARD_H