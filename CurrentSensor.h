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

#ifndef CURRENTSENSOR_H
#define CURRENTSENSOR_H

class CurrentSensor : public ACS712 {

private:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin;

  // DATA
  uint8_t _milliampere;

public:

  // ########################################################################## CONSTRUCTORS

  CurrentSensor(uint8_t _sensor_pin);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t _sensor_pin);
  void set_milliampere(uint8_t milliampere);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  uint8_t get_milliampere(void);

  // ########################################################################## OTHER

  bool initialize(void);
  bool read_current(void);
};

#endif  // CURRENTSENSOR_H