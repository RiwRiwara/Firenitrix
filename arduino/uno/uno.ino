// ================== Library ==================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ================== Constant ==================
LiquidCrystal_I2C lcd(0x27, 16, 2);

int buzzer = 7;
const int mq7Pin = A2;
const int mq9Pin = A3;
const int hMq7pin = 2;
const int hMq9Pin = 3;

const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;

const char* saveApi = "http://192.168.1.238:8000/sensor/event";

int mode = 1;
int modeEmergency = 1;

// ================== Setup ==================
void setup() {

  pinMode(buzzer, OUTPUT);

  // Sensors
  pinMode(hMq7pin, OUTPUT);
  digitalWrite(hMq7pin, HIGH);
  pinMode(hMq9Pin, OUTPUT);
  digitalWrite(hMq9Pin, HIGH);

  // Buttons
  pinMode(buttonPin8, INPUT_PULLUP);
  pinMode(buttonPin9, INPUT_PULLUP);
  pinMode(buttonPin10, INPUT_PULLUP);

  // LCD
  lcd.begin();
  lcd.backlight();
}

// ================== Loop ==================
void loop() {
  Serial.begin(4800);

  // Get button state
  int state4 = digitalRead(buttonPin4);
  int state5 = digitalRead(buttonPin5);
  int state6 = digitalRead(buttonPin6);

  // Mode
  if (state4 == LOW) {
    Serial.begin(9600);
    Serial.println(GetMq9Sensor());
    delay(200);
  }
  if (state5 == LOW) {
    Serial.println("Change Mode");
    Serial.println(mode);
    delay(100);
    if (mode == 1) {
      mode = 2;
    } else if (mode == 2) {
      mode = 3;
    } else if (mode == 3) {
      mode = 1;
    }
    delay(100);
  }
  if (state6 == LOW) {
    Serial.println("Emergency Call!");
    delay(200);
  }

  // Mode toggle
  switch (mode) {
    case 1:
      Serial.println("MQ7");
      ShowTextLine1(GetMq7Sensor());
      ShowTextLine2("MQ7 => Safe");
      break;
    case 2:
      Serial.println("MQ9");
      ShowTextLine1(GetMq9Sensor());
      ShowTextLine2("MQ9 => Safe");
      break;
    case 3:
      Serial.begin(9600);
      char jsonBuffer[256];
      createJsonParams(jsonBuffer, "MQ7", GetMq7Sensor(), "Sensors_data_retrieved_successfully", "OK");
      Serial.print(jsonBuffer);
      delay(1500);

      ShowTextLine1(GetMq9Sensor());
      ShowTextLine2("Auto save to DB : Safe");
      break;
  }


  Serial.end();
  delay(500);
}

// ================== Utilities Functions ==================
void ShowTextLine1(const char* text) {
  lcd.setCursor(0, 0);
  lcd.print(text);
}

void ShowTextLine2(const char* text) {
  lcd.setCursor(0, 1);
  lcd.print(text);
}

float voltageToPPM(float voltage) {
  float voltagePoints[] = { 0.0, 1.0 };
  float ppmPoints[] = { 0.0, 100.0 };

  if (voltage <= voltagePoints[0]) {
    return ppmPoints[0];
  } else if (voltage >= voltagePoints[1]) {
    return ppmPoints[1];
  } else {
    float slope = (ppmPoints[1] - ppmPoints[0]) / (voltagePoints[1] - voltagePoints[0]);
    return ppmPoints[0] + slope * (voltage - voltagePoints[0]);
  }
}

const char* GetMq7Sensor() {
  int sensorValue = analogRead(mq7Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[16];
  String str = "";
  str += ppm;
  str.toCharArray(buffer, 16);
  return buffer;
}

const char* GetMq9Sensor() {
  int sensorValue = analogRead(mq9Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[16];
  String str = "";
  str += ppm;
  str.toCharArray(buffer, 16);
  return buffer;
}

void createJsonParams(char* jsonBuffer, char* sensor_name, char* value, char* description, char* status) {
  sprintf(jsonBuffer, "%s/%s/%s/%s/%s", saveApi, sensor_name, status, value, description);
}
