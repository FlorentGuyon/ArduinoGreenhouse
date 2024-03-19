/**
  * @file     Regulator.h
  * @version  V1.0
  * @date     2024, March 17
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Regulator class
  *
  **/

#ifndef _REGULATOR_H_
#define _REGULATOR_H_

#include <stdint.h> // Definition of the uintX_t types
#include "Switchable.h" // Definition of the Switchable class
#include "Threshold.h" // Definition of the Threshold class

class Regulator : public Switchable::Switchable {

public:

  // ########################################################################## ATTRIBUTES
  
  // DATA
  Threshold** _thresholds; // Minimal/maximal thresold below/above which the switch value will be set to true
  uint8_t _count_thresholds; // Number of thresholds

  // ########################################################################## CONSTRUCTORS

  Regulator();
  Regulator(Threshold** thresholds, uint8_t count_thresholds, uint8_t switch_pin);

  // ########################################################################## SETTERS
  
  void set_thresholds(Threshold** thresholds);
  void set_count_thresholds(uint8_t count_thresholds);

  // ########################################################################## GETTERS
  
  Threshold** get_thresholds();
  Threshold* get_threshold(uint8_t index);
  uint8_t get_count_thresholds(void);

  // ########################################################################## OTHER

  void check_thresholds();
};

#endif  // _REGULATOR_H_
