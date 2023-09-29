//
// Created by Dominic Furchert on 09.07.23.
//

#include "Connected.h"
#include "Disconnected.h"

void Connected::enter(Network *network) {
    Serial.println("Entering Connected Wifi state");
    Serial.println("with IP address: ");
    Serial.println(WiFi.localIP());
    if(WiFiClass::status() != WL_CONNECTED)
        network->switching();
}

void Connected::switching(Network *network) {
    //Connected -> Disconnected
    network->setState(Disconnected::getInstance());
}

void Connected::exit(Network *network) {
    Serial.println("Exiting Connected Wifi state");
}

NetworkState &Connected::getInstance() {
    static Connected singleton;
    return singleton;
}
