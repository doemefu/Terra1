//
// Created by Dominic Furchert on 09.07.23.
//

#ifndef TERRA1_NETWORK_H
#define TERRA1_NETWORK_H


#include "NetworkState.h"
#include "WiFi.h"

class NetworkState;

class Network {
public:
    Network();
    inline NetworkState* getConnectionState() const { return connectionState; }
    void switching();
    void setState(NetworkState& newState);

private:
    NetworkState* connectionState;
};


#endif //TERRA1_NETWORK_H
