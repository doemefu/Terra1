//
// Created by Dominic Furchert on 09.07.23.
//

#include "Network.h"
#include "Disconnected.h"

Network::Network() {
    connectionState = &Disconnected::getInstance();
    Serial.println("Network created");
}

void Network::setState(NetworkState &newState) {
    connectionState->exit(this);
    connectionState = &newState;
    connectionState->enter(this);
}

void Network::switching() {
    connectionState->switching(this);
}