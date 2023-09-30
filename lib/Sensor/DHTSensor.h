//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_DHTSENSOR_H
#define TERRA1_DHTSENSOR_H
#pragma once

#include "Sensor.h"
#include <DHT.h>

class DHTSensor : public Sensor {
public:
    DHTSensor(uint8_t pin, uint8_t type);
    SensorValues readValue() override;
    void readPublishValue(MqttManager *mqttManager) override;

private:
    DHT dht;

};

#endif //TERRA1_DHTSENSOR_H
