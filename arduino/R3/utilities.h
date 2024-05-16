#ifndef UTILITIES_H
#define UTILITIES_H

float voltageToPPM(float voltage);
void createJsonParams(char* jsonBuffer, const char* sensor_name, const char* value, const char* description, const char* status);

#endif
