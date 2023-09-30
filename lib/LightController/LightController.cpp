//
// Created by Dominic Furchert on 04.07.23.
//
#include "LightController.h"

LightController::LightController(RelayController *relayController) {
    this->relayController = relayController;
    lightState = OFF;
}

bool LightController::turnLightOn() {
    lightState = ON;
    return relayController->channelOn(MyRelay::lightChannel);  // Using relayController instance
}

bool LightController::turnLightOff() {
    lightState = OFF;
    return relayController->channelOff(MyRelay::lightChannel);  // Using relayController instance
}

StateEnum LightController::getLightState() {
    return lightState;
}
