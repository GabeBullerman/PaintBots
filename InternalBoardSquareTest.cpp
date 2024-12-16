// @author: Gabriel Bullerman
#include "InternalBoardSquare.h"
#include "ITest.h"
#include <iostream>
#include <type_traits>
#include <cassert>

class InternalBoardSquareTest : public ITest {
public:
    // doTests method: Runs all the tests and returns true if all pass, false otherwise.
    bool doTests() override {
        return testInheritance();
    }

private:
    // testInheritance method: Checks if InternalBoardSquare is a subclass of BoardSquare.
    bool testInheritance() {
        bool isBase = std::is_base_of<BoardSquare, InternalBoardSquare>::value;
        assert(isBase); // Assert that InternalBoardSquare is a subclass of BoardSquare.
        std::cout << "Checking inheritance: PASS\n";
        return isBase;
    }
};

int main() {
    std::cout << "InternalBoardSquare class unit tests\n";
    InternalBoardSquareTest test;
    if (test.doTests()) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
    return 0;
}