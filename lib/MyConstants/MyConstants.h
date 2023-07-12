//
// Created by Dominic Furchert on 04.07.23.
//


#ifndef TERRA1_MYCONSTANTS_H
#define TERRA1_MYCONSTANTS_H
#include "DHT.h"

namespace MyDHT
{
    extern const int Pin;     // The DHT Pin
    extern const uint8_t Type;   // The DHT Type
}
namespace MyDallasTemperature
{
    extern const int Pin;     // The DallasTemperature Pin
}

namespace WifiDetails
{
    extern const char* SSID;
    extern const char* Password;
}

namespace MqttDetails {
    extern const char* Server;
    extern const int Port;
}

namespace Timing {
    extern const int measureWait;
}
#endif //TERRA1_MYCONSTANTS_H