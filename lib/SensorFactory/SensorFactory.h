//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_SENSORFACTORY_H
#define TERRA1_SENSORFACTORY_H
#pragma once

#include "Sensor.h"
#include "DHTSensor.h"
#include "DallasTemperatureSensor.h"
#include "SHT35.h"
#include <string>
#include "MyConstants.h"

// Factory Pattern
class SensorFactory {
public:
    static Sensor* createSensor(const std::string& sensorType);
    void initSensors(DHT* dhtSensor, DallasTemperature* dallasTemperatureSensor);
};


#endif //TERRA1_SENSORFACTORY_H
