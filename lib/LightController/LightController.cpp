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
    for(auto& observer : observers) {
        observer->onStateChanged("terra1/light", "{\"LightState\": \"ON\"}");
    }
    return relayController->channelOn(MyRelay::lightChannel);  // Using relayController instance
}

bool LightController::turnLightOff() {
    lightState = OFF;
    for(auto& observer : observers) {
        observer->onStateChanged("terra1/light", "{\"LightState\": \"OFF\"}");
    }
    return relayController->channelOff(MyRelay::lightChannel);  // Using relayController instance
}

StateEnum LightController::getLightState() {
    return lightState;
}

void LightController::registerObserver(IStateObserver *observer) {
    observers.push_back(observer);
}
