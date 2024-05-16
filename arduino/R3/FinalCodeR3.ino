#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "sensors.h"
#include "display.h"
#include "utilities.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial UnoSerial(3, 2);  // RX | TX

const int mq7Pin = A2;
const int mq9Pin = A3;
const int hMq7Pin = 4;
const int hMq9Pin = 5;

const int buttonPin1 = 6;
const int buttonPin2 = 7;
const int buttonPin3 = 8;

#define buzzerPin 9

const int ledPin1 = 10;
const int ledPin2 = 11;
const int ledPin3 = 12;

const int tiltPin11 = 13;

int mode = 1;
bool isEmergency = false;

void setup() {
  UnoSerial.begin(57600);
  Serial.begin(9600);

  pinMode(hMq7Pin, OUTPUT);
  digitalWrite(hMq7Pin, HIGH);
  pinMode(hMq9Pin, OUTPUT);
  digitalWrite(hMq9Pin, HIGH);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  lcd.begin();
  lcd.backlight();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

  pinMode(buzzerPin, OUTPUT);
  pinMode(tiltPin11, INPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin1, LOW);
}

void loop() {
  // Refresh loop
  int btn1 = digitalRead(buttonPin1);
  int btn2 = digitalRead(buttonPin2);
  int btn3 = digitalRead(buttonPin3);


  // Button action
  if (btn1 == LOW) {
    Serial.println("[Btn 1 click]");
    EmergencyEnd();
    char jsonBuffer[256];
    alert();
    if (mode == 1) {
      createJsonParams(jsonBuffer, "MQ7", GetMq7Sensor(), "MQ7_Sensors_data_retrieved", GetMq7SensorStatus());
      UnoSerial.print(jsonBuffer);
      UnoSerial.print("\n");
    } else if (mode == 2) {
      createJsonParams(jsonBuffer, "MQ9", GetMq9Sensor(), "MQ9_Sensors_data_retrieved", GetMq9SensorStatus());
      UnoSerial.print(jsonBuffer);
      UnoSerial.print("\n");
    } else if (mode == 3) {
      createJsonParams(jsonBuffer, "Tilt", GetTiltSensor(), "Tils_Sensors_data_retrieved", "OK");
      UnoSerial.print(jsonBuffer);
      UnoSerial.print("\n");
    }
    Serial.println(jsonBuffer);

    delay(200);
  } else if (btn2 == LOW) {
    EmergencyEnd();
    Serial.println("[Btn 2 click]");
    EmergencyEnd();
    alert();

    if (mode == 1) {
      mode = 2;
    } else if (mode == 2) {
      mode = 3;
    } else if (mode == 3) {
      mode = 1;
    }
  } else if (btn3 == LOW) {
    Serial.println("[Btn 3 click]");
    if (isEmergency) {
      EmergencyEnd();
    } else {
      isEmergency = true;
    }
  }

  // Emergency mode
  if (isEmergency) {
    char jsonBuffer[256];
    createJsonParams(jsonBuffer, "Emergency", "Emergency", "Emergency","Emergency");
    UnoSerial.print(jsonBuffer);
    UnoSerial.print("\n");
    EmergencyStart();
  }

  // Mode
  if (mode == 1) {
    if (isEmergency) {

    } else {
      const char* mq7SensorReading = GetMq7Sensor();
      String line1 = "MQ7 : ";
      line1 += mq7SensorReading;
      ShowTextLine1(line1.c_str());
    }

    const char* mq7StatusReading = GetMq7SensorStatus();
    String line2 = "Status : ";
    line2 += mq7StatusReading;
    ShowTextLine2(line2.c_str());
    digitalWrite(ledPin3, HIGH);
    ChangeLedByStatus(mq7StatusReading);

  } else if (mode == 2) {
    if (isEmergency) {
    } else {
      const char* mq9SensorReading = GetMq9Sensor();
      String line91 = "MQ9 : ";
      line91 += mq9SensorReading;
      ShowTextLine1(line91.c_str());
      const char* mq9StatusReading = GetMq9SensorStatus();
      String line92 = "Status : ";
      line92 += mq9StatusReading;
      ShowTextLine2(line92.c_str());
      digitalWrite(ledPin3, HIGH);
      ChangeLedByStatus(mq9StatusReading);
    }
  } else if (mode == 3) {
    if (isEmergency) {
    } else {
      const char* GetTiltSensorReading = GetTiltSensor();
      String lineTilt1 = "Tilt : ";
      lineTilt1 += GetTiltSensorReading;
      ShowTextLine1(lineTilt1.c_str());
      ShowTextLine2("                ");
      digitalWrite(ledPin3, HIGH);
      ChangeLedByStatus(GetTiltSensorReading);
    }
  }
}


void EmergencyStart() {
  Serial.println("Emergency Call!");
  ShowTextLine1("== Emergency ==");
  ShowTextLine2("Come out quickly!");
  digitalWrite(ledPin1, HIGH);
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(ledPin1, LOW);
  digitalWrite(buzzerPin, LOW);
  UnoSerial.print("Emergency Call!");
  UnoSerial.print("\n");
}
void EmergencyEnd() {
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin1, LOW);
  isEmergency = false;
}

void ChangeLedByStatus(const char* status) {
  if (strcmp(status, "Safe") == 0 || strcmp(status, "Normal") == 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
  } else if (strcmp(status, "Warning") == 0 || strcmp(status, "Tilted") == 0) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
  } else if (strcmp(status, "Dangerous") == 0) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
}


void alert() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
}