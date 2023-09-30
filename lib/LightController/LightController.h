//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_LIGHTCONTROLLER_H
#define TERRA1_LIGHTCONTROLLER_H

#include <memory>
#include <unordered_map>
#include "MyConstants.h"
#include "RelayController.h"  // Include RelayController header

class LightController {
public:
    explicit LightController(RelayController *relayController);  // Modified constructor
    bool turnLightOn();
    bool turnLightOff();
    StateEnum getLightState();

private:
    RelayController *relayController;  // Pointer to the RelayController
    StateEnum lightState;
};

#endif //TERRA1_LIGHTCONTROLLER_H
