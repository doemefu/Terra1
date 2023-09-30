//
// Created by Dominic Furchert on 04.07.23.
//
#include "SensorFactory.h"

Sensor* SensorFactory::createSensor(const std::string& sensorType) {
    if (sensorType == "DHT") {
        Serial.println("Hello from the DHT SensorFactory!");
        return new DHTSensor(MyDHT::Pin, MyDHT::Type);
    }
    else if (sensorType == "DS18B20") {
        Serial.println("Hello from the Dallas SensorFactory!");
        return new DallasTemperatureSensor(MyDallasTemperature::Pin);
    }else if (sensorType == "SHT35") {
        Serial.println("Hello from the Sensirion SensorFactory!");
        return new SHTSensor(MySHT35::SCLPIN);
    }
    return nullptr; // If sensorType does not match any known type, return nullptr
}

void SensorFactory::initSensors(DHT *dhtSensor, DallasTemperature *dallasTemperatureSensor) {
    dhtSensor->begin();
    dallasTemperatureSensor->begin();
}
