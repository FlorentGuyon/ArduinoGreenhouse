/**
  * @file     Pulsable.h
  * @version  V1.0
  * @date     2024, March 18
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Pulsable class
  *
  **/

#include <stdint.h> // Definition of the uintX_t types
#include "Thresholdable.h" // Definition of the Thresholdable class

#ifndef _PULSABLE_H_
#define _PULSABLE_H_

class Pulsable : public Thresholdable::Thresholdable {

public:

  // ########################################################################## ATTRIBUTES

  // PIN
  uint8_t _pulse_pin; // digital output

  // ########################################################################## CONSTRUCTORS

  Pulsable(uint8_t _pulse_pin = (uint8_t) -1, Threshold** thresholds = nullptr, uint8_t count_thresholds = 0);

  // ########################################################################## SETTERS
  
  void set_pulse_pin(uint8_t pulse_pin);

  // ########################################################################## GETTERS
  
  uint8_t get_pulse_pin(void);

  // ########################################################################## OTHERS

  void pulse(uint16_t pulse_duration = 100, uint8_t count_pulses = 1, uint16_t pulses_interval = 0);
  void check_thresholds(uint16_t pulse_duration = 100, uint8_t count_pulses = 1, uint16_t pulses_interval = 0);
};

#endif  // _PULSABLE_H_
