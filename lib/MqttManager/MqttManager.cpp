#include "MqttManager.h"
#include <utility>

//Singleton
MqttManager& MqttManager::getInstance(WiFiClient& client) {
    static MqttManager instance(client);
    return instance;
}

void MqttManager::subscribe(const String& topic, CallbackFunction callback) {
    callbackMap[topic] = std::move(callback);
}

void MqttManager::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

MqttManager::MqttManager(WiFiClient& client) : mqttClient(client) {
    Serial.println("MqttManager constructor");
    mqttClient.setServer(MqttDetails::Server, MqttDetails::Port);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->callbackDispatcher(topic, payload, length);
    });
}

void MqttManager::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("terra1")) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }}

void MqttManager::callbackDispatcher(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String inpMessage;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        inpMessage += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "terra2/lamp") {
        Serial.print("Changing output to ");
        if(inpMessage == "lightOn"){
            Serial.println("Turning light On");
            //Dies das kommt noch
        }
        else if(inpMessage == "lightOff"){
            Serial.println("Turning light Off");
            //Dies das kommt noch
        }
    }
    else {
        Serial.println("Unknown topic: " + String(topic));
    }
}

void MqttManager::publish(const String& topic, const String& message) {
    mqttClient.publish(topic.c_str(), message.c_str());
    Serial.println("Published message: " + message + " on topic: " + topic);
}