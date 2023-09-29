//
// Created by Dominic Furchert on 09.07.23.
//

#ifndef TERRA1_CONNECTING_H
#define TERRA1_CONNECTING_H
#pragma once
#include "Network.h"
#include "NetworkState.h"
#include <WiFi.h>
#include "MyConstants.h"

class Connecting : public NetworkState{
public:
    void enter(Network* network) override;
    void switching(Network* network) override;
    void exit(Network* network) override;
    static NetworkState& getInstance();

private:
    Connecting() {}
    Connecting(const Connecting& other);
    Connecting& operator=(const Connecting& other);
};


#endif //TERRA1_CONNECTING_H
