/**
  * @file     LightSensor.h
  * @version  V1.0
  * @date     2024, Marcch 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LightSensor class
  *
  * +5V -> Light Dependent Resistor -> Arduino Uno Analog Pin A0 -> 10kohms Resistor -> Ground
  *
  **/

#include <stdint.h> // Definition of the uint8_t type

#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_

class LightSensor {

private:

  // ########################################################################## ATTRIBUTES

  // PIN
  uint8_t _resistance_pin;

  // DATA
  uint16_t _illuminance;

public:
  
  // ########################################################################## CONSTRUCTORS

  LightSensor(uint8_t resistance_pin);

  // ########################################################################## SETTERS

  void set_resistance_pin(uint8_t resistance_pin);
  void set_illuminance(uint16_t illuminance);

  // ########################################################################## GETTERS
  
  uint8_t get_resistance_pin();
  uint16_t get_illuminance();
  
  // ########################################################################## OTHERS

  void read_illuminance();
};

#endif  // _LIGHTSENSOR_H_
