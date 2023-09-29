//
// Created by Dominic Furchert on 04.07.23.
//
#include "LightController.h"

LightController& LightController::getInstance() {
    static LightController instance;
    return instance;
}

void LightController::addCommand(const std::string& name, std::unique_ptr<LightCommand> command) {
    commands[name] = std::move(command);
}

void LightController::executeCommand(const std::string& name) {
    if (commands.find(name) != commands.end()) {
        commands[name]->execute();
    }
}
