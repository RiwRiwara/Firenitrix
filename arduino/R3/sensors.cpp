#include <Arduino.h>
#include "sensors.h"
#include "utilities.h"

const char* GetMq7Sensor() {
  int sensorValue = analogRead(mq7Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[16];
  String str = String(ppm, 2);
  str.toCharArray(buffer, 16);
  return buffer;
}
const char* GetMq7SensorStatus() {
  int sensorValue = analogRead(mq7Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[32];
  String status = "";

  if (ppm < 50) {
    status = "Safe";
  } else if (ppm < 200) {
    status = "Warning";
  } else {
    status = "Dangerous";
  }

  String str = status;
  str.toCharArray(buffer, 32);
  return buffer;
}



const char* GetMq9Sensor() {
  int sensorValue = analogRead(mq9Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[16];
  String str = String(ppm, 2);
  str.toCharArray(buffer, 16);
  return buffer;
}

const char* GetMq9SensorStatus() {
  int sensorValue = analogRead(mq9Pin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float ppm = voltageToPPM(voltage);

  static char buffer[32];
  String status = "";

  if (ppm < 1000) {
    status = "Safe";
  } else if (ppm < 5000) {
    status = "Warning";

  } else {
    status = "Dangerous";
  }

  String str = status;
  str.toCharArray(buffer, 32);
  return buffer;
}


const char* GetTiltSensor() {
  int sensorValue = digitalRead(tiltPin11);
  static char buffer[16];
  String str = (sensorValue == 0) ? "Normal" : "Tilted";
  if (sensorValue == 1) {
  } else {
  }
  str.toCharArray(buffer, 16);
  return buffer;
}
