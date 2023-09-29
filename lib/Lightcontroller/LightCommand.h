//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_LIGHTCOMMAND_H
#define TERRA1_LIGHTCOMMAND_H
class LightCommand {
public:
    virtual void execute() = 0;
};

class TurnOnLightCommand : public LightCommand {
public:
    void execute() override;
};

class TurnOffLightCommand : public LightCommand {
public:
    void execute() override;
};
#endif //TERRA1_LIGHTCOMMAND_H
