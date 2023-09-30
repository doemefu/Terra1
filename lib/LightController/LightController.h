//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_LIGHTCONTROLLER_H
#define TERRA1_LIGHTCONTROLLER_H

#include <memory>
#include <unordered_map>
#include "MyConstants.h"
#include "RelayController.h"  // Include RelayController header
#include <vector>
#include "IStateObserver.h"

class LightController {
public:
    explicit LightController(RelayController *relayController);  // Modified constructor
    bool turnLightOn();
    bool turnLightOff();
    StateEnum getLightState();
    void registerObserver(IStateObserver* observer);

private:
    RelayController *relayController;  // Pointer to the RelayController
    StateEnum lightState;
    std::vector<IStateObserver*> observers;

};

#endif //TERRA1_LIGHTCONTROLLER_H
