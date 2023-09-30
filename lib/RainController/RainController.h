//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_RAINCONTROLLER_H
#define TERRA1_RAINCONTROLLER_H

#include <memory>
#include <unordered_map>
#include "MyConstants.h"
#include "RelayController.h"  // Include RelayController header

class RainController {
public:
    explicit RainController(RelayController *relayController);  // Modified constructor
    bool turnRainOn();
    bool turnRainOff();
    StateEnum getRainState();
    static long getRainStartTime();
    static void setRainStartTime(long rainStartTime);

private:
    RelayController *relayController;  // Pointer to the RelayController
    StateEnum RainState;
    static long rainStartTime;
};

#endif //TERRA1_RainCONTROLLER_H
