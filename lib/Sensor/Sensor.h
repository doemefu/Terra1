//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_SENSOR_H
#define TERRA1_SENSOR_H
#pragma once

#include "MqttManager.h"
#include "oneWire.h"

class Sensor {
public:
    virtual float readValue() = 0;
    virtual void readPublishValue(MqttManager *mqttManager) = 0;
    virtual ~Sensor() = default;
};

#endif //TERRA1_SENSOR_H
