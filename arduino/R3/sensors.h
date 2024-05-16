#ifndef SENSORS_H
#define SENSORS_H

extern const int mq7Pin;
extern const int mq9Pin;
extern const int tiltPin11;

const char* GetMq7Sensor();
const char* GetMq7SensorStatus();
const char* GetMq9Sensor();
const char* GetMq9SensorStatus();
const char* GetTiltSensor();

#endif
