//
// Created by Dominic Furchert on 09.07.23.
//

#include "Connecting.h"
#include "Connected.h"


void Connecting::enter(Network *network) {
    Serial.println("Entering Connecting Wifi state");

    //WiFiClass::mode(WIFI_STA);
    WiFi.mode(WIFI_STA);

    Serial.print("Connecting to ");
    Serial.println(WifiDetails::SSID);

// Start the Wi-Fi scan
    int scanResult = WiFi.scanNetworks();

    while (scanResult == -2) {
        Serial.print(":");
        delay(500);  // Wait some time for the scan to complete
        scanResult = WiFi.scanComplete();
    }

    Serial.print("Scan result: ");
    Serial.println(scanResult);

    // Print the SSID of each found network
    for (int i = 0; i < scanResult; i++) {
        Serial.print("Network ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(WiFi.SSID(i));
    }

    WiFi.begin(WifiDetails::SSID, WifiDetails::Password);

    //for(int i=0; i <= 30000 && WiFiClass::status() != WL_CONNECTED; i += 500){
    for(int i=0; i <= 30000 && WiFi.status() != WL_CONNECTED; i += 500){
        Serial.print(".");
        Serial.print(WiFi.status());
        delay(500);
    }

    // Check the final status after the connection attempt
    wl_status_t status = WiFi.status();

    if (status == WL_CONNECTED) {
        Serial.println("\nConnected successfully!");
        network->switching();
    } else {
        Serial.println("\nFailed to connect.");
        printWiFiError(status);
    }
}

// Function to print specific error messages based on the Wi-Fi status
void Connecting::printWiFiError(wl_status_t status) {
    switch (status) {
        case WL_NO_SSID_AVAIL:
            Serial.println("Error: SSID not available.");
            break;
        case WL_CONNECT_FAILED:
            Serial.println("Error: Connection failed. Incorrect password?");
            break;
        case WL_IDLE_STATUS:
            Serial.println("Error: Wi-Fi is idle.");
            break;
        case WL_DISCONNECTED:
            Serial.println("Error: Disconnected from the network.");
            break;
        case WL_CONNECTION_LOST:
            Serial.println("Error: Connection lost.");
            break;
        case WL_NO_SHIELD:
            Serial.println("Error: No Wi-Fi hardware found.");
            break;
        default:
            Serial.println("Error: Unknown error occurred.");
            break;
    }
}

void Connecting::switching(Network *network) {
    //Connecting -> Connected
    network->setState(Connected::getInstance());
}

void Connecting::exit(Network *network) {
    Serial.println("Exiting Connecting Wifi state");
}

NetworkState &Connecting::getInstance() {
    static Connecting singleton;
    return singleton;
}
