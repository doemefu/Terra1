//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_DALLASTEMPERATURESENSOR_H
#define TERRA1_DALLASTEMPERATURESENSOR_H
#pragma once

#include "Sensor.h"
#include <DallasTemperature.h>

class DallasTemperatureSensor : public Sensor {
public:
    explicit DallasTemperatureSensor(uint8_t pin);
    float readValue() override;
    void readPublishValue(MqttManager *mqttManager) override;

private:
    OneWire oneWire;
    DallasTemperature ds18b20;
};

#endif //TERRA1_DALLASTEMPERATURESENSOR_H
