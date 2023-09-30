//
// Created by Dominic Furchert on 04.07.23.
//


#ifndef TERRA1_MYCONSTANTS_H
#define TERRA1_MYCONSTANTS_H
#include "DHT.h"

enum StateEnum {
    ON,
    OFF,
    ERROR
};

namespace MyDHT
{
    extern const int Pin;     // The DHT Pin
    extern const uint8_t Type;   // The DHT Type
}
namespace MyDallasTemperature
{
    extern const int Pin;     // The DallasTemperature Pin
}
namespace MySHT35
{
    extern const int SDAPIN;
    extern const int SCLPIN;
    extern const int RSTPIN;
}
namespace MyRelay
{
    extern const int i2cAddress;
    extern const int rainChannel;
    extern const int lightChannel;
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

namespace TimeConfig{
    extern const char* ntpServer;
    extern const long  gmtOffset_sec;
    extern const int   daylightOffset_sec;
}
namespace Timing {
    extern const int measureWait;
    extern long rainStartTime;
    extern long rainDuration;
    extern int lightStartTime;
    extern int lightStopTime;
}
#endif //TERRA1_MYCONSTANTS_H