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
#include "SensorValue.h" // Definition of the SensorValue8Bits types

#ifndef SOILHUMIDITYSENSOR_H
#define SOILHUMIDITYSENSOR_H

class SoilHumiditySensor {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin; // Analog input

  // DATA
  SensorValue8Bits* _humidity; // %

  // ########################################################################## CONSTRUCTORS

  SoilHumiditySensor(uint8_t sensor_pin, uint8_t minimum_acceptable_humidity = 0, uint8_t maximum_acceptable_humidity = 100, uint8_t humidity_tolerance = 100);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t sensor_pin);
  void set_humidity(SensorValue8Bits* humidity);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  SensorValue8Bits* get_humidity(void);

  // ########################################################################## OTHER

  bool read_data(void);
};

#endif  // SOILHUMIDITYSENSOR_H