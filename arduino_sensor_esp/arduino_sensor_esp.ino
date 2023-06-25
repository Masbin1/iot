#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include "DHT.h"

const char* ssid = "kakaka";
const char* password = "00000000";

#define DHTPIN 8
#define DHTTYPE DHT11
const int sensorPin = A2;

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature, nilai;

SoftwareSerial ss(2, 3);

void setup() {
  Serial.begin(9600);
  ss.begin(115200);
  dht.begin();
  connectToWifi();
}

void connectToWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");

  unsigned long startMillis = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startMillis < 5000) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi");
  }
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  nilai = analogRead(sensorPin);

  // Send data to ESP via serial communication
  String sendToESP = String(humidity) + ";" + String(temperature) + ";" + String(nilai);
  ss.println(sendToESP);

  // Display data in the log
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Nilai: ");
  Serial.println(nilai);

  delay(10000);
}
