//
// Created by Dominic Furchert on 09.07.23.
//

#include "Disconnected.h"
#include "Connecting.h"

void Disconnected::enter(Network *network) {
    Serial.println("Entering Disconnected Wifi state, triggering connecting phase");
    network->switching();
}

void Disconnected::switching(Network *network) {
    //Disconnected -> Connecting
    network->setState(Connecting::getInstance());
}

void Disconnected::exit(Network *network) {
    Serial.println("Exiting Disonnected Wifi state");

}

NetworkState &Disconnected::getInstance() {
    static Disconnected singleton;
    return singleton;
}
