#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "kakaka";
const char* password = "00000000";

WiFiClient client;
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

String splitString(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void kirimDataKeServer() {
  HTTPClient http;
  String postData;
  String url;

  postData = String("humidity=") + humidity + "&temperature=" + temperature + "&nilai=" + nilai;

  url = "http://192.168.43.128/arduino/kirimkeserver.php"; // local
  // url = "http://findkost.000webhostapp.com/kirimkeserver.php"; // online

  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();
}

void loop() {
  if (Serial.available()) {
    String msg;
    while (Serial.available()) {
      msg += char(Serial.read());
      delay(50);
    }
    humidity = splitString(msg, ';', 0).toFloat();
    temperature = splitString(msg, ';', 1).toFloat();
    nilai = splitString(msg, ';', 2).toFloat();
    msg = "";
  }

  currentMillis = millis();
  if ((currentMillis - prevMillis) >= intervalMillis) {
    kirimDataKeServer();
    prevMillis = currentMillis;
  }
}
