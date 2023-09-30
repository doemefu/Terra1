//
// Created by Dominic Furchert on 09.07.23.
//

#ifndef TERRA1_CONNECTED_H
#define TERRA1_CONNECTED_H

#include "Network.h"
#include "NetworkState.h"

class Connected : public NetworkState {
public:
    void enter(Network* network) override;
    void switching(Network* network) override;
    void exit(Network* network) override;
    static NetworkState& getInstance();

private:
    Connected() {}
    Connected(const Connected& other);
    Connected& operator=(const Connected& other);
};


#endif //TERRA1_CONNECTED_H
