#ifndef ROBOTAGENTROSTER_H
#define ROBOTAGENTROSTER_H

#include <vector>
#include <string>
#include "IRobotAgent.h"

class RobotAgentRoster {
public:
    static RobotAgentRoster* getInstance();

    void add(IRobotAgent* agent);
    IRobotAgent* operator[](size_t index) const;
    IRobotAgent* operator[](const std::string& name) const;

private:
    RobotAgentRoster() = default;
    static RobotAgentRoster* instance;
    std::vector<IRobotAgent*> agents;
};

#endif // ROBOTAGENTROSTER_H