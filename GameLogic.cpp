#include "GameBoard.h"
#include "PlainDisplay.h"
#include "Config.h"
#include "GameLogic.h"
#include "RobotAgentRoster.h"
#include "lazyRobot.h"
#include "AntiRandom.h"
#include "RandomRobot.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

GameLogic::GameLogic() : pause(false) {}

void GameLogic::playGame(const std::string& boardconfig, const std::string& robotconfig) {
    std::cout << "Loading board configuration from: " << boardconfig << std::endl;
    Config config(boardconfig);
    GameBoard* gameBoard = GameBoard::getInstance("xyzzy", config);
    PlainDisplay display(gameBoard);

    std::cout << "Opening robot configuration file: " << robotconfig << std::endl;
    std::ifstream file(robotconfig);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open robot configuration file.");
    }

    std::string redRobotName, blueRobotName;
    std::getline(file, redRobotName);
    std::getline(file, blueRobotName);
    std::cout << "Red robot strategy: " << redRobotName << std::endl;
    std::cout << "Blue robot strategy: " << blueRobotName << std::endl;

    Robot redRobot, blueRobot;
    redRobot.setColor(RobotColor::RED_ROBOT);
    blueRobot.setColor(RobotColor::BLUE_ROBOT);

    std::cout << "Setting red robot agent..." << std::endl;
    redRobot.setRobotAgent(RobotAgentRoster::getInstance()->operator[](redRobotName));
    std::cout << "Setting blue robot agent..." << std::endl;
    blueRobot.setRobotAgent(RobotAgentRoster::getInstance()->operator[](blueRobotName));

    int moveCount = 0;
    const int maxMoves = 300;
    int redHitDuration = 0;
    int blueHitDuration = 0;

    RobotMoveRequest* redMove = nullptr;
    RobotMoveRequest* blueMove = nullptr;

    // Display the initial board
    std::cout << "Initial board:" << std::endl;
    display.display();
    std::cout << std::endl;

    // Start the game paused if required
    if (pause) {
        pauseGame();
    }

    bool gameEnded = false;
    std::string winner;

    while (moveCount < maxMoves && !gameEnded) {
        std::cout << "Turn #" << moveCount << std::endl;

        // Get moves from robots
        redMove = redRobot.getRobotAgent()->getMove(gameBoard->getShortRangeScan(RobotColor::RED_ROBOT), gameBoard->getLongRangeScan());
        if (!redMove) {
            std::cerr << "Error: Red robot did not return a move." << std::endl;
            break;
        }
        blueMove = blueRobot.getRobotAgent()->getMove(gameBoard->getShortRangeScan(RobotColor::BLUE_ROBOT), gameBoard->getLongRangeScan());
        if (!blueMove) {
            std::cerr << "Error: Blue robot did not return a move." << std::endl;
            break;
        }

        // Perform red robot move
        bool redMoveSuccess = gameBoard->MoveRobot(*redMove);

        // Check for game-ending conditions
        if (!redMoveSuccess) {
            std::cout << "Game-ending condition met: Red robot ran into an obstacle. Blue robot wins!" << std::endl;
            winner = "Blue robot";
            gameEnded = true;
            display.display();
            std::cout << std::endl;
            break;
        }

        // Perform blue robot move
        bool blueMoveSuccess = gameBoard->MoveRobot(*blueMove);

        // Check for game-ending conditions
        if (!blueMoveSuccess) {
            std::cout << "Game-ending condition met: Blue robot ran into an obstacle. Red robot wins!" << std::endl;
            winner = "Red robot";
            gameEnded = true;
            display.display();
            std::cout << std::endl;
            break;
        }

        // Check for robot collision
        if (gameBoard->checkRobotCollision(RobotColor::RED_ROBOT) || gameBoard->checkRobotCollision(RobotColor::BLUE_ROBOT)) {
            std::cout << "Game-ending condition met: Robots collided." << std::endl;
            if (redMove->move != NONE && blueMove->move == NONE) {
                std::cout << "Red robot moved into blue robot. Red robot loses." << std::endl;
                winner = "Blue robot";
            } else if (blueMove->move != NONE && redMove->move == NONE) {
                std::cout << "Blue robot moved into red robot. Blue robot loses." << std::endl;
                winner = "Red robot";
            } else {
                std::cout << "Both robots moved into each other. It's a tie." << std::endl;
                winner = "None";
            }
            gameEnded = true;
            std::cout << std::endl;
            break;
        }

        // Handle paint blob hits
        if (redMove->shoot && gameBoard->PaintBlobHit(*redMove)) {
            blueHitDuration = config.getHitDuration();
            std::cout << "Red robot hit blue robot with paint blob. Blue robot will paint red for " << blueHitDuration << " turns." << std::endl;
        }

        if (blueMove->shoot && gameBoard->PaintBlobHit(*blueMove)) {
            redHitDuration = config.getHitDuration();
            std::cout << "Blue robot hit red robot with paint blob. Red robot will paint blue for " << redHitDuration << " turns." << std::endl;
        }

        // Decrease hit durations
        if (redHitDuration > 0) {
            redHitDuration--;
        }

        if (blueHitDuration > 0) {
            blueHitDuration--;
        }

        if (pause) {
            pauseGame();
        }

        moveCount++;
    }

    // Determine the winner if the game did not end early
    if (!gameEnded) {
        std::cout << "Determining the winner..." << std::endl;
        int redScore = gameBoard->redScore();
        int blueScore = gameBoard->blueScore();
        if (redScore > blueScore) {
            winner = "Red robot";
        } else if (blueScore > redScore) {
            winner = "Blue robot";
        } else {
            winner = "None";
        }
        std::cout << "Final Score - Red robot: " << redScore << ", Blue robot: " << blueScore << std::endl;
    }

    if (winner == "None") {
        std::cout << "It's a tie!" << std::endl;
    } else {
        std::cout << winner << " wins!" << std::endl;
    }

    // Clean up
    std::cout << "Cleaning up..." << std::endl;
    delete redMove;
    delete blueMove;
}

void GameLogic::setPause(bool pausemode) {
    pause = pausemode;
}

void GameLogic::pauseGame() const {
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <boardconfig> <robotconfig>" << std::endl;
        return 1;
    }

    // Get the instance of the RobotAgentRoster
    RobotAgentRoster* roster = RobotAgentRoster::getInstance();

    // Add agents to the roster
    roster->add(new AntiRandom());
    roster->add(new RandomRobot());
    roster->add(new lazyRobot());

    // Start the game
    GameLogic game;
    game.setPause(true);
    game.playGame(argv[1], argv[2]);

    return 0;
}