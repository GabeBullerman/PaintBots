// @author: Gabriel Bullerman
#include "ExternalBoardSquare.h"
#include "ITest.h"
#include <iostream>
#include <type_traits>
#include <cassert>

class ExternalBoardSquareTest : public ITest {
public:
    // Runs all the tests and returns true if all pass, false otherwise.
    bool doTests() override {
        return testInheritance();
    }

private:
    // Checks if ExternalBoardSquare is a subclass of BoardSquare.
    bool testInheritance() {
        bool isBase = std::is_base_of<BoardSquare, ExternalBoardSquare>::value;
        assert(isBase);
        std::cout << "Checking inheritance: PASS\n";
        return isBase;
    }
};

int main() {
    std::cout << "ExternalBoardSquare class unit tests\n";
    ExternalBoardSquareTest test;
    if (test.doTests()) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
    return 0;
}