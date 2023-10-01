//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_DHTSENSOR_H
#define TERRA1_DHTSENSOR_H


#include "Sensor.h"
#include <DHT.h>

class DHTSensor : public Sensor {
public:
    DHTSensor(uint8_t pin, uint8_t type);
    SensorValues readValue() override;
    void readPublishValue(MqttManager *mqttManager) override;
    int getHumidity() override;

private:
    DHT dht;
    SensorValues sensorData;

};

#endif //TERRA1_DHTSENSOR_H
