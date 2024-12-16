CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: ConfigTest BoardSquareTest InternalBoardSquareTest ExternalBoardSquareTest GameBoardTest paintbots

ConfigTest: ConfigTest.o Config.o
	$(CXX) $(CXXFLAGS) -o ConfigTest ConfigTest.o Config.o

BoardSquareTest: BoardSquareTest.o BoardSquare.o
	$(CXX) $(CXXFLAGS) -o BoardSquareTest BoardSquareTest.o BoardSquare.o

InternalBoardSquareTest: InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o
	$(CXX) $(CXXFLAGS) -o InternalBoardSquareTest InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o

ExternalBoardSquareTest: ExternalBoardSquareTest.o ExternalBoardSquare.o InternalBoardSquare.o BoardSquare.o
	$(CXX) $(CXXFLAGS) -o ExternalBoardSquareTest ExternalBoardSquareTest.o ExternalBoardSquare.o InternalBoardSquare.o BoardSquare.o

GameBoardTest: GameBoardTest.o GameBoard.o Config.o InternalBoardSquare.o BoardSquare.o ExternalBoardSquare.o
	$(CXX) $(CXXFLAGS) -o GameBoardTest GameBoardTest.o GameBoard.o Config.o InternalBoardSquare.o BoardSquare.o ExternalBoardSquare.o

paintbots: GameLogic.o GameBoard.o Config.o InternalBoardSquare.o BoardSquare.o ExternalBoardSquare.o PlainDisplay.o Robot.o lazyRobot.o RandomRobot.o AntiRandom.o RobotAgentRoster.o
	$(CXX) $(CXXFLAGS) -o paintbots GameLogic.o GameBoard.o Config.o InternalBoardSquare.o BoardSquare.o ExternalBoardSquare.o PlainDisplay.o Robot.o lazyRobot.o RandomRobot.o AntiRandom.o RobotAgentRoster.o

RandomRobot.o: RandomRobot.cpp
	$(CXX) $(CXXFLAGS) -c RandomRobot.cpp

AntiRandom.o: AntiRandom.cpp
	$(CXX) $(CXXFLAGS) -c AntiRandom.cpp

RobotAgentRoster.o: RobotAgentRoster.cpp
	$(CXX) $(CXXFLAGS) -c RobotAgentRoster.cpp

clean:
	rm -f *.o ConfigTest BoardSquareTest InternalBoardSquareTest ExternalBoardSquareTest GameBoardTest paintbots