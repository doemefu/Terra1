//
// Created by Dominic Furchert on 04.07.23.
//
#include "DallasTemperatureSensor.h"

DallasTemperatureSensor::DallasTemperatureSensor(uint8_t pin) : oneWire(pin), ds18b20(&oneWire) {
    ds18b20.begin();
    Serial.println("DallasTemperatureSensor initialized");
}

SensorValues DallasTemperatureSensor::readValue() {
    ds18b20.requestTemperatures();
    sensorData.temperature = ds18b20.getTempCByIndex(0);
    return sensorData;
}

void DallasTemperatureSensor::readPublishValue(MqttManager *mqttManager) {
    Serial.println("DallasTemperatureSensor::readPublishValue");
    delay(1000);
    ds18b20.requestTemperatures(); // Send the command to get temperatures
    float tempC = ds18b20.getTempCByIndex(0);

    Serial.print("Temperature for the device 1 (index 0) is: " + String(tempC));
    if (tempC != DEVICE_DISCONNECTED_C){
        Serial.print("Temperature for the device 1 (index 0) is: ");
        Serial.println(tempC);

        char tempCstr[8];
        dtostrf(tempC, 1, 2, tempCstr);
        mqttManager->publish("terra1/DS18B20/temp", tempCstr, false);
    }else{
        Serial.println("Error: Could not read temperature data");
    }
}

int DallasTemperatureSensor::getHumidity() {
    return sensorData.humidity;
}
