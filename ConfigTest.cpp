// @author Gabriel Bullerman
#include "Config.h"
#include "ITest.h"
#include <iostream>
#include <cassert>

// ConfigTest class: Tests the Config class.
class ConfigTest : public ITest {
public:
    // Runs all the tests and returns true if all pass, false otherwise.
    bool doTests() override {
        return testDefaultConstructor() && testBadFileName() && testValidConfigFile() && testMissingParameters() && testInvalidConfigFile() && testCaseInsensitivity() && testExtraWhitespace() && testCommentLines() && testBlankLines() && testMixedOrder();
    }

private:
    // Tests the default constructor.
    bool testDefaultConstructor() {
        Config config;
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking default constructor: PASS\n";
        return true;
    }

    // Tests handling of a bad file name.
    bool testBadFileName() {
        try {
            Config config("nonexistent.cfg");
        } catch (const std::exception& e) {
            std::cout << "Checking bad file name: PASS\n";
            return true;
        }
        return false;
    }

    // Tests a valid configuration file.
    bool testValidConfigFile() {
        Config config("valid_config.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking valid config file: PASS\n";
        return true;
    }

    // Tests handling of missing parameters.
    bool testMissingParameters() {
        Config config("missing_params.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking missing parameters: PASS\n";
        return true;
    }

    // Tests handling of an invalid configuration file.
    bool testInvalidConfigFile() {
        try {
            Config config("invalid_config.cfg");
        } catch (const std::exception& e) {
            std::cout << "Checking invalid config file: PASS\n";
            return true;
        }
        return false;
    }

    // Tests case insensitivity in the configuration file.
    bool testCaseInsensitivity() {
        Config config("case_insensitive.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking case insensitivity: PASS\n";
        return true;
    }

    // Tests handling of extra whitespace in the configuration file.
    bool testExtraWhitespace() {
        Config config("extra_whitespace.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking extra whitespace: PASS\n";
        return true;
    }

    // Tests handling of comment lines in the configuration file.
    bool testCommentLines() {
        Config config("comment_lines.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking comment lines: PASS\n";
        return true;
    }

    // Tests handling of blank lines in the configuration file.
    bool testBlankLines() {
        Config config("blank_lines.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking blank lines: PASS\n";
        return true;
    }

    // Tests handling of mixed order in the configuration file.
    bool testMixedOrder() {
        Config config("mixed_order.cfg");
        assert(config.getHitDuration() == 28);
        assert(config.getPaintBlobLimit() == 30);
        assert(config.getRockLowerBound() == 10);
        assert(config.getRockUpperBound() == 12);
        assert(config.getFogLowerBound() == 2);
        assert(config.getFogUpperBound() == 8);
        assert(config.getLongRangeLimit() == 26);
        std::cout << "Checking mixed order: PASS\n";
        return true;
    }
};

// Main function: Entry point of the test program.
int main() {
    std::cout << "Config class unit tests\n";
    ConfigTest test;
    if (test.doTests()) {
        std::cout << "All tests passed.\n";
    } else {
        std::cout << "Some tests failed.\n";
    }
    return 0;
}