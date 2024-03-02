#include "MqttManager.h"
#include <utility>

//Singleton
MqttManager& MqttManager::getInstance(WiFiClient& client, LightController *lightController, RainController *rainController){
    static MqttManager instance(client, lightController, rainController);
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

MqttManager::MqttManager(WiFiClient& client, LightController *lightController, RainController *rainController) : mqttClient(client) {
    Serial.println("MqttManager constructor");
    mqttClient.setServer(MqttDetails::Server, MqttDetails::Port);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->callbackDispatcher(topic, payload, length);
    });
    this->lightController = lightController;
    this->rainController = rainController;
}

void MqttManager::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("terra1", "terra1/mqtt/status", 0, true, "{\"MqttState\": 0}")) {
            Serial.println("connected");
            mqttClient.publish("terra1/mqtt/status", "{\"MqttState\": 1}", true);
            mqttClient.subscribe("terra1/light/man");
            mqttClient.subscribe("terra1/rain/man");
            mqttClient.subscribe("terraGeneral/light/schedule");
            mqttClient.subscribe("terraGeneral/rain/schedule");
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

    if (String(topic) == "terra1/light/man") {
        if(inpMessage == "{\"LightState\": 1}"){
            Serial.println("Turning light On");
            lightController->turnLightOn();
        }
        else if(inpMessage == "{\"LightState\": 0}"){
            Serial.println("Turning light Off");
            lightController->turnLightOff();
        }
    } else if (String(topic) == "terra1/rain/man") {
        if(inpMessage == "{\"RainState\": 1}"){
            Serial.println("Turning rain On");
            rainController->turnRainOn();
        }
        else if(inpMessage == "{\"RainState\": 0}"){
            Serial.println("Turning rain Off");
            rainController->turnRainOff();
        }
    } else if (String(topic) == "terraGeneral/light/schedule") {
        if(inpMessage == "{\"LightState\": 1}"){
            Serial.println("Turning light On");
            lightController->turnLightOn();
        }
        else if(inpMessage == "{\"LightState\": 0}"){
            Serial.println("Turning light Off");
            lightController->turnLightOff();
        }
    } else if (String(topic) == "terraGeneral/rain/schedule") {
        if(inpMessage == "{\"RainState\": 1}"){
            Serial.println("Turning rain On");
            rainController->turnRainOn();
        }
        else if(inpMessage == "{\"RainState\": 0}"){
            Serial.println("Turning rain Off");
            rainController->turnRainOff();
        }
    } else {
        Serial.println("Unknown topic: " + String(topic));
    }
}

void MqttManager::publish(const String& topic, const String& message, const bool& retain){
    mqttClient.publish(topic.c_str(), message.c_str(), retain);
    Serial.println("Published message: " + message + " on topic: " + topic);
}
