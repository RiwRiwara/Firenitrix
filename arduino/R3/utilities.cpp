#include "utilities.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>


float voltageToPPM(float voltage) {
  float voltagePoints[] = {0.0, 5.0};  
  float ppmPoints[] = {0.0, 1000.0};   

  if (voltage <= voltagePoints[0]) {
    return ppmPoints[0];
  } else if (voltage >= voltagePoints[1]) {
    return ppmPoints[1];
  } else {
    float slope = (ppmPoints[1] - ppmPoints[0]) / (voltagePoints[1] - voltagePoints[0]);
    return ppmPoints[0] + slope * (voltage - voltagePoints[0]);
  }
}

void createJsonParams(char* jsonBuffer, const char* sensor_name, const char* value, const char* description, const char* status) {
  sprintf(jsonBuffer, "{\"sensor\":\"%s\", \"status\":\"%s\", \"value\":\"%s\", \"description\":\"%s\"}", sensor_name, status, value, description);
}
