//
// Created by Dominic Furchert on 04.07.23.
//
#include "RainController.h"
#include "TimeController.h"

long RainController::rainStartTime = 0;

RainController::RainController(RelayController *relayController) {
    this->relayController = relayController;
    RainState = OFF;
}

bool RainController::turnRainOn() {
    rainStartTime = millis();
    RainState = ON;
    for(auto& observer : observers) {
        observer->onStateChanged("terra1/rain", "{\"RainState\": \"ON\"}", true);
    }
    return relayController->channelOn(MyRelay::rainChannel);  // Using relayController instance
}

bool RainController::turnRainOff() {
    Serial.println("RainController::turnRainOff()");
    RainState = OFF;
    for(auto& observer : observers) {
        observer->onStateChanged("terra1/rain", "{\"RainState\": \"OFF\"}", true);
    }
    return relayController->channelOff(MyRelay::rainChannel);  // Using relayController instance
}

StateEnum RainController::getRainState() {
    return RainState;
}

long RainController::getRainStartTime() {
    return rainStartTime;
}

void RainController::setRainStartTime(long rainStartTime) {
    RainController::rainStartTime = rainStartTime;
}

void RainController::registerObserver(IStateObserver *observer) {
    observers.push_back(observer);
}
