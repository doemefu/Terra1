#include <Arduino.h>
#include "SensorFactory.h"
#include "Sensor.h"
#include "MqttManager.h"
#include "Network.h"

Network network;
Sensor* dhtSensor;
Sensor* ds18b20Sensor;
MqttManager* mqttManager;
WiFiClient espClient;

List<Sensor*> sensors;

unsigned long lastDHTMeasurement = 0;

void setup(){
    Serial.begin(9600);
    delay(5000);
    Serial.println("starting setup");

    //while (!Serial) { }

    //network = Network();


    mqttManager = &MqttManager::getInstance(espClient);
    /*
    mqttManager.subscribe("topic", [](const String& message) {
        // Do something with the message
        Serial.println(message);
    });
    */
    dhtSensor = SensorFactory::createSensor("DHT");
    ds18b20Sensor = SensorFactory::createSensor("DS18B20");

    Serial.println("setup done, now entering loop");
}

void loop() {
    while(WiFiClass::status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        network.switching();
    }

    mqttManager->loop();
    if (millis() - lastDHTMeasurement > Timing::measureWait){
        ds18b20Sensor->readPublishValue(mqttManager);
        Serial.println("ds done");
        dhtSensor->readPublishValue(mqttManager);
        Serial.println("dht done");
        lastDHTMeasurement = millis();
    }
}