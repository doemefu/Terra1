#ifndef RELAY_CONTROLLER_H
#define RELAY_CONTROLLER_H

#include <Arduino.h>
#include <Wire.h>  // Include Arduino Wire library for I2C
#include "multi_channel_relay.h"
#include "MyConstants.h"

struct RelayState {
    StateEnum channel1;
    StateEnum channel2;
    StateEnum channel3;
    StateEnum channel4;
};

class RelayController {
private:
    Multi_Channel_Relay relay;

public:
    // Constructor
    explicit RelayController(uint8_t address);

    // Turn on a channel
    boolean channelOn(uint8_t channel);

    // Turn off a channel
    boolean channelOff(uint8_t channel);

    // Set channel state
    boolean setChannelState(uint8_t channel, bool state);

    StateEnum getChannelState(uint8_t channel);
};

#endif  // RELAY_CONTROLLER_H
