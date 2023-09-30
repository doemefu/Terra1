//
// Created by Dominic Furchert on 29.09.23.
//

#ifndef TERRA1_TIMECONTROLLER_H
#define TERRA1_TIMECONTROLLER_H

#include "MyConstants.h"
#include <ctime>

class TimeController {

public:
    explicit TimeController();
    void loop();
    void printLocalTime();

    static int getHours();

    static int getMinutes();

    static int getSeconds();

private:
    time_t now;
    struct tm* timeinfo;
    int lastSync = -1;
    static int hours;
    static int minutes;
    static int seconds;
    void time_sync();
    void time_setup();

};


#endif //TERRA1_TIMECONTROLLER_H
