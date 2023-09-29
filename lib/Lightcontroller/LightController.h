//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_LIGHTCONTROLLER_H
#define TERRA1_LIGHTCONTROLLER_H

#include <memory>
#include <unordered_map>
#include "LightCommand.h"

class LightController {
public:
    static LightController& getInstance();
    void addCommand(const std::string& name, std::unique_ptr<LightCommand> command);
    void executeCommand(const std::string& name);

private:
    LightController() = default;
    std::unordered_map<std::string, std::unique_ptr<LightCommand>> commands;
};

#endif //TERRA1_LIGHTCONTROLLER_H
