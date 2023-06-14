#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature;

SoftwareSerial ss(2,3); 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 ss.begin(115200);
 dht.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:

 humidity = dht.readHumidity();
  temperature = dht.readTemperature();
 
 //kirim data ke ESP melalui komunikasi serial 
 String sendToESP = "";
 sendToESP += humidity;
 sendToESP += ";";
 sendToESP += temperature;
 ss.println(sendToESP);
 delay(1000);
}