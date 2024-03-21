/**
  * @file     SoilHumiditySensor.h
  * @version  V1.0
  * @date     2024, March 20
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SoilHumiditySensor class
  *
  * Soil Humidity Sensor DO  Pin -> None 
  * Soil Humidity Sensor AO  Pin -> Arduino Analog A2 Pin
  * Soil Humidity Sensor Gnd Pin -> Ground
  * Soil Humidity Sensor VCC Pin -> +5V
  *
  **/

#include <stdint.h> // Definition of the uintX_t types

#ifndef SOILHUMIDITYSENSOR_H
#define SOILHUMIDITYSENSOR_H

class SoilHumiditySensor {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin; // Analog input

  // DATA
  uint8_t _humidity; // %

  // ########################################################################## CONSTRUCTORS

  SoilHumiditySensor(uint8_t sensor_pin);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t sensor_pin);
  void set_humidity(uint8_t humidity);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  uint8_t get_humidity(void);

  // ########################################################################## OTHER

  void read_data(void);
};

#endif  // SOILHUMIDITYSENSOR_H