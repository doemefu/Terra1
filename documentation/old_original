#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#include <PubSubClient.h>
#include <Wire.h>
#include "DHT.h"
#include <DallasTemperature.h>


// Replace the next variables with your SSID/Password combination

const char* ssid = "Quellbrunnen";
const char* password = "Fam1Furchert!";

//const char* ssid = "Dominics iPhone";
//const char* password = "passworT";

//const char* ssid = "LERNKUBE";
//const char* password = "l3rnk4b3";

//const char* ssid = "impacthub";
//const char* password = "coworking@ImpactHub";



// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "cloud.tbz.ch";

WiFiClient espClient;
PubSubClient client(espClient);
long lastInfluxMsg = 0;
long lastMqttMsg = 0;
char msg[50];
int value = 0;

// InfluxDB  server url. Don't use localhost, always server name or ip address.
// E.g. http://192.168.1.48:8086 (In InfluxDB 2 UI -> Load Data -> Client Libraries),
#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
// InfluxDB 2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "rbXFBU4BSfHHBfF_Hcaefrf8hNr0yi22Qn9rLjyCqra4cRK5lOVW52E60rPKwMkj3itIleF3kYxOSMcuFkHcQw=="
// InfluxDB 2 organization id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "doemesPlants"
// InfluxDB 2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "m153"


//DHT11 things
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


//DS18B20 temp sensor
#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//Photoresistror
int soilPin = 35; // select the input pin for the potentiometer
int soilValue = 0; // variable to store the value coming from the senso

//soil Resistor
int photoPin = 36; // select the input pin for the potentiometer
int photoValue = 0; // variable to store the value coming from the senso


void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //wificlientsecure.connect()

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    //WiFi.addAP(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void turnOnLight(){
    //relay_SetStatus(ON);
    client.publish("terra1/light", "1");
}
void turnOffLight(){
    //relay_SetStatus(OFF);
    client.publish("terra1/light", "0");
}


void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String inpMessage;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        inpMessage += (char)message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    if (String(topic) == "terra1/light") {
        Serial.print("Changing output to ");
        if(inpMessage == "lightOn"){
            Serial.println("Turning light On");
            turnOnLight();
        }
        else if(inpMessage == "lightOff"){
            Serial.println("Turning light Off");
            turnOffLight();
        }
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // Subscribe
            client.subscribe("terra1/light");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}


void setup() {
    Serial.begin(9600);
    Serial.println("now Setting up");
    delay(6000);
    Serial.println("now Setting up");
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    //status = bme.begin();

    setup_wifi();
    Serial.println("Wifi-done");
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    //relay_init();

    //dht setup
    dht.begin();

    //DS18B20 setup
    sensors.begin();

}

void loop() {
    if (!client.connected()) {
        Serial.println("disconected");
        reconnect();
    }
    client.loop();

    //get dht
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();

    //get DS18B20
    sensors.requestTemperatures(); // Send the command to get temperatures
    float tempC = sensors.getTempCByIndex(0);

    //Photoresistor
    //Serial.println("Photoresistor value:");
    photoValue = analogRead(photoPin);
    //Serial.println(photoValue, DEC);

    //Soil resistor
    //Serial.println("Soilresistor value:");
    soilValue = analogRead(soilPin);
    //Serial.println(soilValue, DEC);



    long nowMQTT = millis();
    if (nowMQTT - lastMqttMsg > 30000) {
        lastMqttMsg = nowMQTT;


        if (isnan(humi) || isnan(temp)) {
            Serial.println(F("Failed to read from DHT sensor!"));
            //client.publish("terra1/sensor", "error");
            //return;
        }else{
            // Convert the value to a char array
            char tempString[8];
            dtostrf(temp, 1, 2, tempString);
            Serial.print("Temperature: ");
            Serial.println(tempString);
            client.publish("terra1/DHT11/temp", tempString);

            // Convert the value to a char array
            char humString[8];
            dtostrf(humi, 1, 2, humString);
            Serial.print("Humidity: ");
            Serial.println(humString);
            client.publish("terra1/DHT11/humi", humString);
        }


        // DS18B20
        //Check if reading was successful
        if (tempC != DEVICE_DISCONNECTED_C){
            Serial.print("Temperature for the device 1 (index 0) is: ");
            Serial.println(tempC);

            char tempCstr[8];
            dtostrf(tempC, 1, 2, tempCstr);
            client.publish("terra1/DS18B20/temp", tempCstr);
        }else{
            Serial.println("Error: Could not read temperature data");
        }

        // Photoresistor
        char photoStr[8];
        dtostrf(photoValue, 1, 2, photoStr);
        client.publish("terra1/photoResistor/light", photoStr);
        Serial.println("Photoresistor value: ");
        Serial.println(photoStr);


        // Soil resistor
        char soilStr[8];
        dtostrf(soilValue, 1, 2, soilStr);
        client.publish("terra1/soilResistor/soilHumi", soilStr);
        Serial.println("Soilresistor value: ");
        Serial.println(soilStr);

    }



}


