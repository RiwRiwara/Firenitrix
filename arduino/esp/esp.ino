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

void sendPostRequest(const char* url, const char* postData) {
  HTTPClient http;
  http.begin(url);

  // Set content type header
  http.addHeader("Content-Type", "application/json");

  // Send the POST request
  int httpResponseCode = http.POST(postData);

  // Check for response
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Response: ");
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}



// SETUP FUNCTION
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  connectToWiFi();

  String response = sendGetRequest("http://192.168.1.238:8000/sensor/test");
  Serial.println("API Response:");
  Serial.println(response);

  const char* eventData = "{\"sensor_name\":\"TemperatureSensor\",\"value\":25.5,\"status\":\"OK\",\"description\":\"Temperature within normal range\"}";
  sendPostRequest("http://192.168.1.238:8000/sensor/event", eventData);
}

void loop() {
  String receivedMessage = Serial2.readString();
  Serial.println(receivedMessage);
  String response = sendGetRequest(receivedMessage);
  delay(1000);
}

