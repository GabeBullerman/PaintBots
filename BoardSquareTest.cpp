// @author: Gabriel Bullerman
#include "BoardSquare.h"
#include "ITest.h"
#include <iostream>
#include <cassert>

class BoardSquareTest : public ITest {
public:
    // Runs all the tests and returns true if all pass, false otherwise.
    bool doTests() override {
        return testDefaultConstructor() && testParameterizedConstructor();
    }

private:
    // Tests the default constructor.
    bool testDefaultConstructor() {
        BoardSquare square;
        assert(square.getSquareColor() == WHITE);
        assert(square.getSquareType() == EMPTY);
        assert(!square.redRobotPresent());
        assert(!square.blueRobotPresent());
        assert(square.robotDirection() == NORTH);
        std::cout << "Checking default constructor: PASS\n";
        return true;
    }

    // Tests the parameterized constructor.
    bool testParameterizedConstructor() {
        BoardSquare square(RED, ROCK, true, false, SOUTH);
        assert(square.getSquareColor() == RED);
        assert(square.getSquareType() == ROCK);
        assert(square.redRobotPresent());
        assert(!square.blueRobotPresent());
        assert(square.robotDirection() == SOUTH);
        std::cout << "Checking parameterized constructor: PASS\n";
        return true;
    }
};

int main() {
    std::cout << "BoardSquare class unit tests\n";
    BoardSquareTest test;
    if (test.doTests()) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
    return 0;
}