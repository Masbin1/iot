#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "DHT.h"
#include <SoftwareSerial.h>

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
