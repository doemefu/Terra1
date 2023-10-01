//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_DALLASTEMPERATURESENSOR_H
#define TERRA1_DALLASTEMPERATURESENSOR_H


#include "Sensor.h"
#include <DallasTemperature.h>

class DallasTemperatureSensor : public Sensor {
public:
    explicit DallasTemperatureSensor(uint8_t pin);
    SensorValues readValue() override;
    void readPublishValue(MqttManager *mqttManager) override;
    int getHumidity() override;

private:
    OneWire oneWire;
    DallasTemperature ds18b20;
    SensorValues sensorData;
};

#endif //TERRA1_DALLASTEMPERATURESENSOR_H
