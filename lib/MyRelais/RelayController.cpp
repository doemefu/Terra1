#include "RelayController.h"

RelayState relayState;

RelayController::RelayController(uint8_t address) : relay() {
    relay.begin(address);
    relay.channelCtrl(0);
    relayState.channel1 = OFF;
    relayState.channel2 = OFF;
    relayState.channel3 = OFF;
    relayState.channel4 = OFF;
  }

boolean RelayController::channelOn(uint8_t channel) {
    relay.turn_on_channel(channel);
    switch (channel) {
        case 1:
            relayState.channel1 = ON;
            break;
        case 2:
            relayState.channel2 = ON;
            break;
        case 3:
            relayState.channel3 = ON;
            break;
        case 4:
            relayState.channel4 = ON;
            break;
        default:
            Serial.println("Invalid channel number");
            return false;
            break;
    }
    return true;
}

boolean RelayController::channelOff(uint8_t channel) {
    relay.turn_off_channel(channel);
    switch (channel) {
        case 1:
            relayState.channel1 = OFF;
            break;
        case 2:
            relayState.channel2 = OFF;
            break;
        case 3:
            relayState.channel3 = OFF;
            break;
        case 4:
            relayState.channel4 = OFF;
            break;
        default:
            Serial.println("Invalid channel number");
            return false;
    }
    return true;
}

boolean RelayController::setChannelState(uint8_t channel, bool state) {
    switch (channel) {
        case 1:
            if (state) {
                relay.turn_on_channel(1);
            } else {
                relay.turn_off_channel(1);
            }
            break;
        case 2:
            if (state) {
                relay.turn_on_channel(2);
            } else {
                relay.turn_off_channel(2);
            }
            break;
        case 3:
            if (state) {
                relay.turn_on_channel(3);
            } else {
                relay.turn_off_channel(3);
            }
            break;
        case 4:
            if (state) {
                relay.turn_on_channel(4);
            } else {
                relay.turn_off_channel(4);
            }
            break;
        default:
            Serial.println("Invalid channel number");
            return false;
    }
    return true;
}

StateEnum RelayController::getChannelState(uint8_t channel) {
    switch (channel) {
        case 1:
            return relayState.channel1;
        case 2:
            return relayState.channel2;
        case 3:
            return relayState.channel3;
        case 4:
            return relayState.channel4;
        default:
            Serial.println("Invalid channel number");
            return ERROR;
    }
}
