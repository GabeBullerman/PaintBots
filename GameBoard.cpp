#include "GameBoard.h"
#include <stdexcept>
#include <random>
#include <iostream>

// Initialize the static instance pointer to nullptr.
GameBoard* GameBoard::instance = nullptr;

// Returns the singleton instance of the GameBoard.
GameBoard* GameBoard::getInstance(const std::string& password) {
    if (password == "xyzzy") {
        if (!instance) {
            instance = new GameBoard();
        }
        return instance;
    }
    return nullptr;
}

// Returns the singleton instance of the GameBoard with a configuration.
GameBoard* GameBoard::getInstance(const std::string& password, const Config& config) {
    if (password == "xyzzy") {
        if (!instance) {
            instance = new GameBoard(config);
        }
        return instance;
    }
    return nullptr;
}

// Default constructor: Initializes the GameBoard with default configuration.
GameBoard::GameBoard() : GameBoard(Config()) {}

// Parameterized constructor: Initializes the GameBoard with the specified configuration.
GameBoard::GameBoard(const Config& config) {
    initializeBoard(config);
}

// Initializes the game board with the specified configuration.
void GameBoard::initializeBoard(const Config& config) {
    std::cout << "Initializing game board..." << std::endl;
    board.resize(17, std::vector<InternalBoardSquare>(17));

    // Set up walls on the edges of the board
    for (int i = 0; i < 17; ++i) {
        board[0][i].setSquareType(WALL);
        board[16][i].setSquareType(WALL);
        board[i][0].setSquareType(WALL);
        board[i][16].setSquareType(WALL);
    }

    placeRocksAndFog(config);
    placeRobots();
    notifyObservers(); // Notify observers once after initialization
}

// Places rocks and fog on the game board based on the configuration.
void GameBoard::placeRocksAndFog(const Config& config) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rockDist(config.getRockLowerBound(), config.getRockUpperBound());
    std::uniform_int_distribution<> fogDist(config.getFogLowerBound(), config.getFogUpperBound());
    std::uniform_int_distribution<> posDist(1, 15);

    int numRocks = rockDist(gen);
    int numFog = fogDist(gen);

    for (int i = 0; i < numRocks; ++i) {
        int row = posDist(gen);
        int col = posDist(gen);
        board[row][col].setSquareType(ROCK);
    }

    for (int i = 0; i < numFog; ++i) {
        int row = posDist(gen);
        int col = posDist(gen);
        board[row][col].setSquareType(FOG);
    }
}

// Places the robots on the game board.
void GameBoard::placeRobots() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> posDist(1, 15);

    int redRow = posDist(gen);
    int redCol = posDist(gen);
    board[redRow][redCol].setRedRobotPresent(true);
    std::cout << "Placed red robot at (" << redRow << ", " << redCol << ")" << std::endl;

    int blueRow, blueCol;
    do {
        blueRow = posDist(gen);
        blueCol = posDist(gen);
    } while (blueRow == redRow && blueCol == redCol);

    board[blueRow][blueCol].setBlueRobotPresent(true);
    std::cout << "Placed blue robot at (" << blueRow << ", " << blueCol << ")" << std::endl;
}

// Returns a reference to the square at the specified row and column.
InternalBoardSquare& GameBoard::getSquare(int row, int col) {
    if (row < 0 || row > 16 || col < 0 || col > 16) {
        throw std::out_of_range("Row or column out of range");
    }
    return board[row][col];
}

// Performs the requested move on the designated robot.
bool GameBoard::MoveRobot(const RobotMoveRequest& mr) {
    std::cout << "Robot Moving: " << (mr.robot == RobotColor::RED_ROBOT ? "Red" : "Blue") << std::endl;
    int row = -1, col = -1;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if ((mr.robot == RobotColor::RED_ROBOT && board[r][c].redRobotPresent()) ||
                (mr.robot == RobotColor::BLUE_ROBOT && board[r][c].blueRobotPresent())) {
                row = r;
                col = c;
                break;
            }
        }
        if (row != -1 && col != -1) break;
    }

    if (row == -1 || col == -1) {
        std::cout << "Robot not found on the board" << std::endl;
        return false;
    }

    int newRow = row, newCol = col;
    switch (mr.move) {
        case FORWARD:
            if (board[row][col].robotDirection() == NORTH) newRow--;
            else if (board[row][col].robotDirection() == SOUTH) newRow++;
            else if (board[row][col].robotDirection() == EAST) newCol++;
            else if (board[row][col].robotDirection() == WEST) newCol--;
            break;
        case BACKWARD:
            if (board[row][col].robotDirection() == NORTH) newRow++;
            else if (board[row][col].robotDirection() == SOUTH) newRow--;
            else if (board[row][col].robotDirection() == EAST) newCol--;
            else if (board[row][col].robotDirection() == WEST) newCol++;
            break;
        case ROTATELEFT:
            if (board[row][col].robotDirection() == NORTH) board[row][col].setRobotDirection(WEST);
            else if (board[row][col].robotDirection() == SOUTH) board[row][col].setRobotDirection(EAST);
            else if (board[row][col].robotDirection() == EAST) board[row][col].setRobotDirection(NORTH);
            else if (board[row][col].robotDirection() == WEST) board[row][col].setRobotDirection(SOUTH);
            notifyObservers();
            return true;
        case ROTATERIGHT:
            if (board[row][col].robotDirection() == NORTH) board[row][col].setRobotDirection(EAST);
            else if (board[row][col].robotDirection() == SOUTH) board[row][col].setRobotDirection(WEST);
            else if (board[row][col].robotDirection() == EAST) board[row][col].setRobotDirection(SOUTH);
            else if (board[row][col].robotDirection() == WEST) board[row][col].setRobotDirection(NORTH);
            notifyObservers();
            return true;
        case NONE:
            return true;
    }

    if (newRow < 0 || newRow > 16 || newCol < 0 || newCol > 16 || board[newRow][newCol].getSquareType() == ROCK) {
        std::cout << "Move is invalid or blocked" << std::endl;
        return false;
    }

    if (mr.robot == RobotColor::RED_ROBOT) {
        board[row][col].setRedRobotPresent(false);
        board[newRow][newCol].setRedRobotPresent(true);
    } else {
        board[row][col].setBlueRobotPresent(false);
        board[newRow][newCol].setBlueRobotPresent(true);
    }

    board[row][col].setSquareColor(mr.robot == RobotColor::RED_ROBOT ? RED : BLUE);
    notifyObservers(); // Notify observers after each move

    // Check for collision after the move
    if (checkRobotCollision(mr.robot)) {
        return false;
    }

    return true;
}

// Checks if a paint blob fired by the specified robot would hit the other robot.
bool GameBoard::PaintBlobHit(const RobotMoveRequest& mr) {
    int row = -1, col = -1;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if ((mr.robot == RobotColor::RED_ROBOT && board[r][c].redRobotPresent()) ||
                (mr.robot == RobotColor::BLUE_ROBOT && board[r][c].blueRobotPresent())) {
                row = r;
                col = c;
                break;
            }
        }
        if (row != -1 && col != -1) break;
    }

    if (row == -1 || col == -1) {
        std::cout << "Robot not found on the board" << std::endl;
        return false;
    }

    int targetRow = row, targetCol = col;
    switch (mr.direction) {
        case NORTH: targetRow--; break;
        case SOUTH: targetRow++; break;
        case EAST: targetCol++; break;
        case WEST: targetCol--; break;
    }

    if (targetRow < 0 || targetRow > 16 || targetCol < 0 || targetCol > 16 || board[targetRow][targetCol].getSquareType() == ROCK) {
        return false;
    }

    if ((mr.robot == RobotColor::RED_ROBOT && board[targetRow][targetCol].blueRobotPresent()) ||
        (mr.robot == RobotColor::BLUE_ROBOT && board[targetRow][targetCol].redRobotPresent())) {
        return true;
    }

    return false;
}

// Checks if a robot has moved into the space occupied by the other robot.
bool GameBoard::checkRobotCollision(RobotColor movingRobot) {
    int redRow = -1, redCol = -1, blueRow = -1, blueCol = -1;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if (board[r][c].redRobotPresent()) {
                redRow = r;
                redCol = c;
            }
            if (board[r][c].blueRobotPresent()) {
                blueRow = r;
                blueCol = c;
            }
        }
    }

    if (redRow == blueRow && redCol == blueCol) {
        std::cout << "Collision detected at (" << redRow << ", " << redCol << ")" << std::endl;
        return true;
    }
    return false;
}

// Returns the number of blue squares on the board.
int GameBoard::blueScore() const {
    int score = 0;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if (board[r][c].getSquareColor() == BLUE) {
                score++;
            }
        }
    }
    return score;
}

// Returns the number of red squares on the board.
int GameBoard::redScore() const {
    int score = 0;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if (board[r][c].getSquareColor() == RED) {
                score++;
            }
        }
    }
    return score;
}

// Sets the square color in the board.
void GameBoard::setSquareColor(int row, int col, Color c) {
    board[row][col].setSquareColor(c);
}

// Sets the specified robot to paint a specific color.
void GameBoard::setRobotPaintColor(RobotColor robot, Color sc) {
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            InternalBoardSquare& square = board[r][c];
            if ((robot == RobotColor::RED_ROBOT && square.redRobotPresent()) ||
                (robot == RobotColor::BLUE_ROBOT && square.blueRobotPresent())) {
                square.setSquareColor(sc);
            }
        }
    }
}

// Returns the gameboard as a 2-D array of ExternalBoardSquares.
ExternalBoardSquare** GameBoard::getLongRangeScan() {
    ExternalBoardSquare** scan = new ExternalBoardSquare*[17];
    for (int i = 0; i < 17; ++i) {
        scan[i] = new ExternalBoardSquare[17];
        for (int j = 0; j < 17; ++j) {
            scan[i][j] = ExternalBoardSquare(board[i][j]);
        }
    }
    return scan;
}

// Returns the shortrange scan centered on the specified robot as a 2-D array of ExternalBoardSquares.
ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc) {
    ExternalBoardSquare** scan = new ExternalBoardSquare*[5];
    for (int i = 0; i < 5; ++i) {
        scan[i] = new ExternalBoardSquare[5];
    }

    int centerRow = -1, centerCol = -1;
    for (int r = 0; r < 17; ++r) {
        for (int c = 0; c < 17; ++c) {
            if ((rc == RobotColor::RED_ROBOT && board[r][c].redRobotPresent()) ||
                (rc == RobotColor::BLUE_ROBOT && board[r][c].blueRobotPresent())) {
                centerRow = r;
                centerCol = c;
                break;
            }
        }
        if (centerRow != -1 && centerCol != -1) break;
    }

    if (centerRow == -1 || centerCol == -1) {
        std::cout << "Robot not found on the board" << std::endl;
        return scan;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int r = centerRow - 2 + i;
            int c = centerCol - 2 + j;
            if (r >= 0 && r < 17 && c >= 0 && c < 17) {
                scan[i][j] = ExternalBoardSquare(board[r][c]);
            } else {
                scan[i][j] = ExternalBoardSquare();
            }
        }
    }

    return scan;
}