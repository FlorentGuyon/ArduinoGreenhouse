/**
  * @file     Switchable.h
  * @version  V1.0
  * @date     2024, February 26
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Switchable class
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include "Thresholdable.h" // Definition of the Thresholdable class

#ifndef _SWITCHABLE_H_
#define _SWITCHABLE_H_

class Switchable : public Thresholdable::Thresholdable {

public:

  // ########################################################################## ATTRIBUTES

  // PIN
  uint8_t _switch_pin; // digital output
  
  // DATA
  bool _switch_value;

  // ########################################################################## CONSTRUCTORS

  Switchable(uint8_t switch_pin = (uint8_t) -1, Threshold** thresholds = nullptr, uint8_t count_thresholds = 0);

  // ########################################################################## SETTERS
  
  void set_switch_pin(uint8_t switch_pin);
  bool set_switch_value(bool switch_value);

  // ########################################################################## GETTERS
  
  uint8_t get_switch_pin();
  bool get_switch_value();

  // ########################################################################## OTHER

  void turn_switch_on();
  void turn_switch_off();
  void toggle_switch();
  void check_thresholds();
};

#endif  // _SWITCHABLE_H_
