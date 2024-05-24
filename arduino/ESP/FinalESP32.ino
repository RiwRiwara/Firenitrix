#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

const char* ssid = "Kaboom_2.4G";
const char* password = "0406092549";
const char* host = "192.168.1.10"; // IP address of your FastAPI server
const int port = 8000;

SoftwareSerial NodeSerial(D2, D3); // RX | TX
const char* saveApi = "/sensor/event";

void setup() {
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  NodeSerial.begin(57600);
  Serial.println();
  Serial.println("NodeMCU/ESP8266 Run");

  connectToWiFi();
}

void loop() {
  static char buffer[100]; 
  static int index = 0;    

  while (NodeSerial.available() > 0) {
    char incomingChar = NodeSerial.read(); 
    if (incomingChar == '\n') {
      buffer[index] = '\0';
      Serial.println(buffer);
      sendData(buffer);
      index = 0;
    } else {
      buffer[index] = incomingChar;
      index++;
      if (index >= sizeof(buffer)) {
        index = 0;
      }
    }
  }
}

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(host);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
}

void sendData(const char* data) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("Connection to server failed");
    return;
  }

  Serial.println("Connected to server");

  // Make a HTTP POST request
  client.print(String("POST ") + saveApi + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + strlen(data) + "\r\n\r\n" +
               data + "\r\n");

  delay(10);
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  client.stop();
}
