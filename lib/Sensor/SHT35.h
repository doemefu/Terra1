//
// Created by Dominic Furchert on 29.09.23.
//

#ifndef TERRA1_SHT35_H
#define TERRA1_SHT35_H
#pragma once

#include "Seeed_SHT35.h"
#include "Sensor.h"

class SHTSensor : public Sensor {
public:
    explicit SHTSensor(int SCLPIN);
    SensorValues readValue() override;
    void readPublishValue(MqttManager *mqttManager) override;

private:
    SHT35 sht;
};

#endif //TERRA1_SHT35_H
