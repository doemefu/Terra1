//
// Created by Dominic Furchert on 04.07.23.
//
#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {
    dht.begin();
}

SensorValues DHTSensor::readValue() {
    SensorValues result;
    result.temperature = dht.readTemperature();
    return result;
}

void DHTSensor::readPublishValue(MqttManager *mqttManager) {
    char tempString[16];
    char humiString[16];
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();

    if (isnan(humi) || isnan(temp))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    dtostrf(temp, 1, 2, tempString);
    dtostrf(humi, 1, 2, humiString);

    Serial.println("Temperature: ");
    Serial.println(tempString);
    mqttManager->publish("terra2/DHT11/temp", tempString);
    delay(200);
    Serial.println("Humidity: ");
    Serial.println(humiString);
    mqttManager->publish("terra2/DHT11/humi", humiString);
}
