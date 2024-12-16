// @author: Gabriel Bullerman
#include "Config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Default constructor: Initializes configuration values with default settings.
Config::Config() {
    configValues["HIT_DURATION"] = DEFAULT_HIT_DURATION;
    configValues["PAINTBLOB_LIMIT"] = DEFAULT_PAINTBLOB_LIMIT;
    configValues["ROCK_LOWER_BOUND"] = DEFAULT_ROCK_LOWER_BOUND;
    configValues["ROCK_UPPER_BOUND"] = DEFAULT_ROCK_UPPER_BOUND;
    configValues["FOG_LOWER_BOUND"] = DEFAULT_FOG_LOWER_BOUND;
    configValues["FOG_UPPER_BOUND"] = DEFAULT_FOG_UPPER_BOUND;
    configValues["LONG_RANGE_LIMIT"] = DEFAULT_LONG_RANGE_LIMIT;
}

// Constructor that parses a configuration file.
Config::Config(const std::string& filePath) : Config() {
    parseConfigFile(filePath);
}

// Parses the configuration file.
void Config::parseConfigFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open configuration file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

        std::istringstream iss(line);
        std::string key, equalSign;
        int value;
        if (!(iss >> key >> equalSign >> value) || equalSign != "=") {
            throw std::runtime_error("Invalid configuration file format.");
        }

        for (auto& c : key) c = toupper(c); // Convert key to uppercase
        configValues[key] = value;
    }
}

// Getter methods for configuration values.
int Config::getHitDuration() const { return configValues.at("HIT_DURATION"); }
int Config::getPaintBlobLimit() const { return configValues.at("PAINTBLOB_LIMIT"); }
int Config::getRockLowerBound() const { return configValues.at("ROCK_LOWER_BOUND"); }
int Config::getRockUpperBound() const { return configValues.at("ROCK_UPPER_BOUND"); }
int Config::getFogLowerBound() const { return configValues.at("FOG_LOWER_BOUND"); }
int Config::getFogUpperBound() const { return configValues.at("FOG_UPPER_BOUND"); }
int Config::getLongRangeLimit() const { return configValues.at("LONG_RANGE_LIMIT"); }