//
// Created by Dominic Furchert on 04.07.23.
//
#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : dht(pin, type) {
    dht.begin();
}

SensorValues DHTSensor::readValue() {
    sensorData.temperature = dht.readTemperature();
    return sensorData;
}

void DHTSensor::readPublishValue(MqttManager *mqttManager) {
    char tempString[16];
    char humiString[16];
    sensorData.temperature = dht.readTemperature();
    sensorData.humidity = dht.readHumidity();

    if (isnan(sensorData.humidity) || isnan(sensorData.humidity))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    dtostrf(sensorData.temperature, 1, 2, tempString);
    dtostrf(sensorData.humidity, 1, 2, humiString);

    Serial.println("Temperature: ");
    Serial.println(tempString);
    mqttManager->publish("terra1/DHT11/temp", tempString, false);
    delay(200);
    Serial.println("Humidity: ");
    Serial.println(humiString);
    mqttManager->publish("terra1/DHT11/humi", humiString, false);
}

int DHTSensor::getHumidity() {
    return sensorData.humidity;
}
