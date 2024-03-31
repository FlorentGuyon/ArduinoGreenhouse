/**
  * @file     CurrentSensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the CurrentSensor class
  *
  * ACS712 Gnd Pin -> Ground
  * ACS712 Out Pin -> Arduino Analog A1 Pin (Current)
  * ACS712 VCC Pin -> +5V
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <ACS712.h> // https://www.arduino.cc/reference/en/libraries/acs712/
#include "SensorValue.h" // Definition of the SensorValue16Bits class

#ifndef CURRENTSENSOR_H
#define CURRENTSENSOR_H

class CurrentSensor : public ACS712 {

private:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin;

  // DATA
  SensorValue16Bits* _milliampere;

public:

  // ########################################################################## CONSTRUCTORS

  CurrentSensor(uint8_t _sensor_pin, uint8_t minimum_acceptable_milliampere = 0, uint8_t maximum_acceptable_milliampere = 3000, uint8_t milliampere_tolerance = 3000);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t _sensor_pin);
  void set_milliampere(SensorValue16Bits* milliampere);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  SensorValue16Bits* get_milliampere(void);

  // ########################################################################## OTHER

  void initialize(void);
  bool read_current(void);
};

#endif  // CURRENTSENSOR_H