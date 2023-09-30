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
namespace MySHT35
{
    const int SDAPIN = 21;
    const int SCLPIN = 22;
    const int RSTPIN = 2;
}
namespace MyRelay
{
    const int i2cAddress = 0x11;
    const int lightChannel = 4;
    const int rainChannel = 2;
}
namespace WifiDetails
{
    const char* SSID = "Quellbrunnen";
    const char* Password = "Fam1Furchert!";
    //const char* SSID = "Dominics iPhone";
    //const char* Password = "passworT";
}

namespace MqttDetails {
    const char* Server = "cloud.tbz.ch";
    const int Port = 1883;
}
namespace TimeConfig{
    const char* ntpServer = "pool.ntp.org";
    const long  gmtOffset_sec = 3600;
    const int   daylightOffset_sec = 3600;
}
namespace Timing {
    const int measureWait = 30000;
    long rainStartTime;
    long rainDuration = 20000;
    int lightStartTime = 9;
    int lightStopTime = 18;
}