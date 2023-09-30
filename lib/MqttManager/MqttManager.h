//
// Created by Dominic Furchert on 04.07.23.
//

#ifndef TERRA1_MQTTMANAGER_H
#define TERRA1_MQTTMANAGER_H
#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <map>
#include <functional>
#include "MyConstants.h"
#include "LightController.h"
#include "RainController.h"

class MqttManager {
public:
    using CallbackFunction = std::function<void(const String&)>;

    static MqttManager& getInstance(WiFiClient& client, LightController* lightController, RainController* rainController);

    void subscribe(const String& topic, CallbackFunction callback);

    void loop();

    void publish(const String &topic, const String &message);

    void operator=(MqttManager const&) = delete;
    MqttManager(MqttManager const&) = delete;


private:
    PubSubClient mqttClient;
    std::map<String, CallbackFunction> callbackMap;

    explicit MqttManager(WiFiClient &client, LightController *lightController, RainController *rainController);  // Private constructor

    void reconnect();

    void callbackDispatcher(char* topic, byte* payload, unsigned int length);

    LightController *lightController;  // Pointer to the RelayController
    RainController *rainController;  // Pointer to the RelayController

};

#endif //TERRA1_MQTTMANAGER_H
