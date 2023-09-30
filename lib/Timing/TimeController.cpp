//
// Created by Dominic Furchert on 29.09.23.
//

#include "TimeController.h"

int TimeController::hours = 0;
int TimeController::minutes = 0;
int TimeController::seconds = 0;

TimeController::TimeController() {
    time_setup();
    loop();
    printLocalTime();
}

void TimeController::time_setup(){
    // Richten Sie die Systemzeit mit einem Zeitserver ein
    configTime(TimeConfig::gmtOffset_sec, TimeConfig::daylightOffset_sec, TimeConfig::ntpServer);
    Serial.println("Systemzeit wird synchronisiert");
}

void TimeController::time_sync(){

    // Lesen Sie die aktuelle Zeit in Sekunden seit dem 1. Januar 1970
    now = time(nullptr);

    // Lesen Sie das aktuelle Datum und die aktuelle Uhrzeit aus der aktuellen Zeit
    timeinfo = localtime(&now);

    // Synchronisieren Sie die Systemzeit einmal am Tag, um Ungenauigkeiten zu minimieren
    if (timeinfo->tm_hour == 1 && timeinfo->tm_min == 0 && lastSync != timeinfo->tm_mday) {
        time_setup();
        lastSync = timeinfo->tm_mday;
    }
}

void TimeController::loop(){
    time_sync();
    hours = timeinfo->tm_hour;
    minutes = timeinfo->tm_min;
    seconds = timeinfo->tm_sec;
    }

void TimeController::printLocalTime(){
    Serial.print("Aktuelle Zeit: ");
    Serial.print(timeinfo->tm_hour);
    Serial.print(":");
    if (timeinfo->tm_min < 10) {
        Serial.print("0");
    }
    Serial.print(timeinfo->tm_min);
    Serial.print(":");
    if (timeinfo->tm_sec < 10) {
        Serial.print("0");
    }
    Serial.println(timeinfo->tm_sec);  Serial.println();
}

int TimeController::getHours() {
    return hours;
}

int TimeController::getMinutes() {
    return minutes;
}

int TimeController::getSeconds() {
    return seconds;
}

