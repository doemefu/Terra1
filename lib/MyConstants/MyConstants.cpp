//
// Created by Dominic Furchert on 11.07.23.
//
//
// Created by Dominic Furchert on 04.07.23.
//

#include "MyConstants.h"

namespace MyDHT
{
    const int Pin = 4;     // The DHT Pin
    const uint8_t Type = DHT11;   // The DHT Type
}
namespace MyDallasTemperature
{
    const int Pin = 14;     // The DallasTemperature Pin
}

namespace WifiDetails
{
    //const char* SSID = "Quellbrunnen";
    //const char* Password = "Fam1Furchert!";
    const char* SSID = "Dominics iPhone";
    const char* Password = "passworT";
}

namespace MqttDetails {
    const char* Server = "cloud.tbz.ch";
    const int Port = 1883;
}

namespace Timing {
    const int measureWait = 30000;
}