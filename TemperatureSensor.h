/**
  * @file     humiditySensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the humiditySensor class
  *
  * AM2302  +  Pin -> Ground
  * AM2302 Out Pin -> Arduino Digital 13 Pin (Temperature and temperature)
  * AM2302  -  Pin -> +5V
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <AM2302-Sensor.h> // Definition of the AM2302-Sensor class

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

class TemperatureSensor : public AM2302::AM2302_Sensor {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin;

  bool _is_ready;

  // DATA
  uint8_t _humidity;
  uint8_t _temperature;

  // ########################################################################## CONSTRUCTORS

  TemperatureSensor();
  TemperatureSensor(uint8_t sensor_pin);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t sensor_pin);
  bool set_ready(bool is_ready);
  bool set_humidity(uint8_t humidity);
  bool set_temperature(uint8_t temperature);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  uint8_t get_humidity(void);
  uint8_t get_temperature(void);
  bool is_ready(void);

  // ########################################################################## OTHER

  bool initialize(void);
  bool read_humidity_and_temperature(void);
};

#endif  // TEMPERATURESENSOR_H