#include <Arduino.h>
#include "SensorFactory.h"
#include "Sensor.h"
#include "RelayController.h"
#include "MqttManager.h"
#include "LightController.h"
#include "RainController.h"
#include "TimeController.h"
#include "Network.h"
#include <Wire.h>
#include <esp_task_wdt.h>

//5 seconds WDT
#define WDT_TIMEOUT 5

Network network;
Sensor* sht35Sensor;
RelayController* relayController;
MqttManager* mqttManager;
WiFiClient espClient;
LightController* lightController;
RainController* rainController;
TimeController* timeController;
//List<Sensor*> sensors;

unsigned long lastSensorMeasurement = 0;

void setup(){
    Serial.begin(9600);
    delay(5000);
    Serial.println("starting setup");

    loadConfig();

    sht35Sensor = SensorFactory::createSensor("SHT35");
    relayController = new RelayController(MyRelay::i2cAddress);

    lightController = new LightController(relayController);
    rainController = new RainController(relayController);

    mqttManager = &MqttManager::getInstance(espClient, lightController, rainController);

    lightController->registerObserver(mqttManager);
    rainController->registerObserver(mqttManager);

    network.switching();
    mqttManager->loop();

    lightController->turnLightOff();
    rainController->turnRainOff();

    timeController = new TimeController();

    esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
    esp_task_wdt_add(NULL); //add current thread to WDT watch

    Serial.println("setup done, now entering loop");
}

void loop() {
    while(WiFiClass::status() != WL_CONNECTED) {
        Serial.println("WiFi not connected");
        network.switching();
    }
    timeController->loop();
    mqttManager->loop();

    if (millis() - lastSensorMeasurement > Timing::measureWait){
        sht35Sensor->readPublishValue(mqttManager);
        Serial.println("Measurement done");
        lastSensorMeasurement = millis();
    }

    //if (timeController->getHours() == Timing::lightStartTime && timeController->getMinutes() == 01 && lightController->getLightState() != ON) {
    //    lightController->turnLightOn();
    //}

    //if (timeController->getHours() == Timing::lightStopTime && timeController->getMinutes() == 01 && lightController->getLightState() == ON) {
    //    lightController->turnLightOff();
    //}

    if (sht35Sensor->getHumidity() < 70 && rainController->getRainState() != ON && millis() - rainController->getRainStartTime() > Timing::rainWait) {
        rainController->turnRainOn();
    }

    if (rainController->getRainState() == ON && millis() - rainController->getRainStartTime() > Timing::rainDuration) {
        rainController->turnRainOff();
    }

    esp_task_wdt_reset();
}