#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define RXp2 16
#define TXp2 17

const char* ssid = "Kaboom_2.4G";
const char* password = "0406092549";

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

String sendGetRequest(const char* url) {
  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  String response = "";

  if (httpResponseCode > 0) {
    response = http.getString();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return response;
}



// SETUP FUNCTION
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
 
  connectToWiFi();

  String response = sendGetRequest("http://192.168.1.238:8000/sensor/test");
  Serial.println("API Response:");
  Serial.println(response);

}

void loop() {
  String receivedMessage = Serial2.readString();
  Serial.println(receivedMessage);

  const char* receivedMessageNew = receivedMessage.c_str();
  String response = sendGetRequest(receivedMessageNew);

  delay(1000);
}
