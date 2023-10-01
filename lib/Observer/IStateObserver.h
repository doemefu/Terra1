//
// Created by Dominic Furchert on 01.10.23.
//

#ifndef TERRA1_ISTATEOBSERVER_H
#define TERRA1_ISTATEOBSERVER_H

#include <Arduino.h>

class IStateObserver {
public:
    virtual void onStateChanged(const String& topic, const String& state, const bool& retainFlag) = 0;
};

#endif //TERRA1_ISTATEOBSERVER_H
