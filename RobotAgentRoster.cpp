#include "RobotAgentRoster.h"
#include <iostream>

RobotAgentRoster* RobotAgentRoster::instance = nullptr;

RobotAgentRoster* RobotAgentRoster::getInstance() {
    if (!instance) {
        instance = new RobotAgentRoster();
    }
    return instance;
}

void RobotAgentRoster::add(IRobotAgent* agent) {
    agents.push_back(agent);
}

IRobotAgent* RobotAgentRoster::operator[](size_t index) const {
    if (index >= agents.size()) {
        std::cerr << "Error: Index out of bounds in RobotAgentRoster." << std::endl;
        return nullptr;
    }
    return agents[index];
}

IRobotAgent* RobotAgentRoster::operator[](const std::string& name) const {
    for (auto agent : agents) {
        if (agent->getRobotName() == name) {
            std::cout << "RobotAgentRoster: Found agent with name " << name << std::endl;
            return agent;
        }
    }
    std::cerr << "Error: Agent with name " << name << " not found in RobotAgentRoster." << std::endl;
    return nullptr;
}