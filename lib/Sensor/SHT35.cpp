//
// Created by Dominic Furchert on 29.09.23.
//

#include "SHT35.h"
#include "ArduinoJson.h"

SHTSensor::SHTSensor(int SCLPIN) : sht(SCLPIN) {
    sht.init();
}

SensorValues SHTSensor::readValue() {
    SensorValues result;
    err_t err;

    // Read the data using HIGH_REP_WITH_STRCH setting (high repetition with clock stretch)
    err = sht.read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &result.temperature, &result.humidity);
    if (err != NO_ERROR) {
        // Handle the error case
        // You may assign some invalid values to indicate error
        result.temperature = -1.0f;
        result.humidity = -1.0f;
        Serial.println("Error reading SHT35 sensor");
    }

    return result;
}

void SHTSensor::readPublishValue(MqttManager *mqttManager) {
    // Read the temperature and humidity values from the sensor
    SensorValues sensorData = this->readValue();
    if(sensorData.temperature == -1.0f || sensorData.humidity == -1.0f) {
        StaticJsonDocument<128> jsonErrorDoc;

        jsonErrorDoc["ErrorCode"] = 1;
        jsonErrorDoc["ErrorMessage"] = "Error reading SHT35 sensor";

        String jsonErrorString;
        serializeJson(jsonErrorDoc, jsonErrorString);

        mqttManager->publish("terra1/status/SHT35", jsonErrorString.c_str());  // Converting String to char array using c_str()
        return;
    }
    // Initialize JSON document
    StaticJsonDocument<128> jsonDoc;  // Allocate a static JSON buffer. You may need to adjust the size.

    // Populate JSON object
    jsonDoc["Temperature"] = sensorData.temperature;
    jsonDoc["Humidity"] = sensorData.humidity;

    // Serialize JSON object to string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Publish JSON string
    Serial.println("Publishing Sensor Data as JSON:");
    Serial.println(jsonString);
    mqttManager->publish("terra1/SHT35/data", jsonString.c_str());  // Converting String to char array using c_str()
}

