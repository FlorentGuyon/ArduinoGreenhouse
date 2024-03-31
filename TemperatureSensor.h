/**
  * @file     TemperatureSensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the TemperatureSensor class
  *
  * AM2302  +  Pin -> Ground
  * AM2302 Out Pin -> Arduino Digital 13 Pin (Temperature and temperature)
  * AM2302  -  Pin -> +5V
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <AM2302-Sensor.h> // Definition of the AM2302-Sensor class
#include "SensorValue.h" // Definition of the SensorValue class

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

class TemperatureSensor : public AM2302::AM2302_Sensor {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin;

  bool _is_ready;

  // DATA
  SensorValue8Bits* _humidity;
  SensorValue8Bits* _temperature;

  // ########################################################################## CONSTRUCTORS

  TemperatureSensor(uint8_t sensor_pin, uint8_t minimum_acceptable_temperature = 0, uint8_t maximum_acceptable_temperature = 40, uint8_t temperature_tolerance = 40, uint8_t minimum_acceptable_humidity = 0, uint8_t maximum_acceptable_humidity = 100, uint8_t humidity_tolerance = 100);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t sensor_pin);
  void set_ready(bool is_ready);
  void set_humidity(SensorValue8Bits* humidity);
  void set_temperature(SensorValue8Bits* temperature);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  SensorValue8Bits* get_humidity(void);
  SensorValue8Bits* get_temperature(void);
  bool is_ready(void);

  // ########################################################################## OTHER

  bool initialize(void);
  bool read_humidity_and_temperature(void);
};

#endif  // TEMPERATURESENSOR_H