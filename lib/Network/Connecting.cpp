//
// Created by Dominic Furchert on 09.07.23.
//

#include "Connecting.h"
#include "Connected.h"


void Connecting::enter(Network *network) {
    Serial.println("Entering Connecting Wifi state");

    //WiFiClass::mode(WIFI_STA);
    WiFi.mode(WIFI_STA);

    Serial.print("Connecting to ");
    Serial.println(WifiDetails::SSID);

    WiFi.begin(WifiDetails::SSID, WifiDetails::Password);

    //for(int i=0; i <= 30000 && WiFiClass::status() != WL_CONNECTED; i += 500){
    for(int i=0; i <= 30000 && WiFi.status() != WL_CONNECTED; i += 500){
        Serial.print(".");
        delay(500);
    }

    //if(WiFiClass::status() == WL_CONNECTED){
    if(WiFi.status() == WL_CONNECTED){
        network->switching();
    }else{
        Serial.println("an error has occured during connecting phase");
    }
}

void Connecting::switching(Network *network) {
    //Connecting -> Connected
    network->setState(Connected::getInstance());
}

void Connecting::exit(Network *network) {
    Serial.println("Exiting Connecting Wifi state");
}

NetworkState &Connecting::getInstance() {
    static Connecting singleton;
    return singleton;
}
