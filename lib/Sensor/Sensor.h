//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_SENSOR_H
#define TERRA1_SENSOR_H


#include "MqttManager.h"
#include "oneWire.h"

struct SensorValues{
    float temperature;
    float humidity;
};

class Sensor {
public:
    virtual SensorValues readValue() = 0;
    virtual void readPublishValue(MqttManager *mqttManager) = 0;
    virtual ~Sensor() = default;
    virtual int getHumidity() = 0;

};

#endif //TERRA1_SENSOR_H
