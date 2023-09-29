//
// Created by Dominic Furchert on 09.07.23.
//

#ifndef TERRA1_NETWORKSTATE_H
#define TERRA1_NETWORKSTATE_H
#pragma once
#include "Network.h"

class Network;

class NetworkState {
public:
    virtual void enter(Network* network) = 0;
    virtual void switching(Network* network) = 0;
    virtual void exit(Network* network) = 0;
    virtual ~NetworkState() = default;
};


#endif //TERRA1_NETWORKSTATE_H
