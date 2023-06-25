#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "kakaka";
const char* password = "00000000";
const char* supabaseURL = "https://crcbygicwixbgdtseebc.supabase.co/rest/v1/<tabel>";
const char* supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImNyY2J5Z2ljd2l4YmdkdHNlZWJjIiwicm9sZSI6ImFub24iLCJpYXQiOjE2ODc2NTkzNjcsImV4cCI6MjAwMzIzNTM2N30.vwoIyWlTQNlj5_N7E_2YI7qgqZbCK6BccdCHdnlo08Y";

WiFiClientSecure client;
unsigned long currentMillis = 0, prevMillis = 0, intervalMillis = 2000;
float humidity = 0, temperature = 0, nilai = 0;

void setup() {
  Serial.begin(115200);
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

void kirimDataKeServer() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;

    if (client.connect(supabaseURL, 443)) {
      StaticJsonDocument<200> doc;
      doc["humidity"] = humidity;
      doc["temperature"] = temperature;
      doc["nilai"] = nilai;

      String postData;
      serializeJson(doc, postData);

      client.print("POST ");
      client.print(supabaseURL);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(supabaseURL);
      client.println("Content-Type: application/json");
      client.print("Content-Length: ");
      client.println(postData.length());
      client.print("Authorization: Bearer ");
      client.println(supabaseKey);
      client.println("Connection: close");
      client.println();
      client.println(postData);
      client.println();

      while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
          break;
        }
      }

      String response = client.readStringUntil('\n');
      Serial.println("Server response: " + response);

      client.stop();
    } else {
      Serial.println("Connection to Supabase failed!");
    }
  } else {
    Serial.println("WiFi disconnected!");
  }
}

void loop() {
  // Simulasikan pengambilan data dari sensor atau variabel lain
  humidity = 50.0;
  temperature = 25.0;
  nilai = 123.45;

  // Kirim data ke Supabase
  kirimDataKeServer();

  delay(5000);
}
