//
// Created by Dominic Furchert on 09.07.23.
//

#ifndef TERRA1_DISCONNECTED_H
#define TERRA1_DISCONNECTED_H

#include "Network.h"
#include "NetworkState.h"

class Disconnected : public NetworkState{
public:
    void enter(Network* network) override;
    void switching(Network* network) override;
    void exit(Network* network) override;
    static NetworkState& getInstance();

private:
    Disconnected() {}
    Disconnected(const Disconnected& other);
    Disconnected& operator=(const Disconnected& other);
};


#endif //TERRA1_DISCONNECTED_H
