// @author: Gabriel Bullerman
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
    Config(); // Default constructor
    Config(const std::string& filePath); // Constructor that parses a configuration file

    int getHitDuration() const;
    int getPaintBlobLimit() const;
    int getRockLowerBound() const;
    int getRockUpperBound() const;
    int getFogLowerBound() const;
    int getFogUpperBound() const;
    int getLongRangeLimit() const;

private:
    void parseConfigFile(const std::string& filePath); // Parses the configuration file
    std::unordered_map<std::string, int> configValues; // Stores configuration values

    // Default configuration values
    static const int DEFAULT_HIT_DURATION = 20;
    static const int DEFAULT_PAINTBLOB_LIMIT = 30;
    static const int DEFAULT_ROCK_LOWER_BOUND = 10;
    static const int DEFAULT_ROCK_UPPER_BOUND = 20;
    static const int DEFAULT_FOG_LOWER_BOUND = 5;
    static const int DEFAULT_FOG_UPPER_BOUND = 10;
    static const int DEFAULT_LONG_RANGE_LIMIT = 30;
};

#endif // CONFIG_H