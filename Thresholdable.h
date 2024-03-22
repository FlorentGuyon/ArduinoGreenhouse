/**
  * @file     Thresholdable.h
  * @version  V1.0
  * @date     2024, March 22
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Thresholdable class
  *
  **/

#ifndef _THRESHOLDABLE_H_
#define _THRESHOLDABLE_H_

#include <stdint.h> // Definition of the uintX_t types
#include "Threshold.h" // Definition of the Threshold class

class Thresholdable {

public:

  // ########################################################################## ATTRIBUTES
  
  // DATA
  Threshold** _thresholds; // Minimal/maximal thresold below/above which the switch value will be set to true
  uint8_t _count_thresholds; // Number of thresholds

  // ########################################################################## CONSTRUCTORS

  Thresholdable(Threshold** thresholds = nullptr, uint8_t count_thresholds = 0);

  // ########################################################################## SETTERS
  
  void set_thresholds(Threshold** thresholds);
  void set_count_thresholds(uint8_t count_thresholds);

  // ########################################################################## GETTERS
  
  Threshold** get_thresholds(void);
  Threshold* get_threshold(uint8_t index);
  uint8_t get_count_thresholds(void);

  // ########################################################################## OTHER

  bool are_thresholds_reached(void);
};

#endif  // _THRESHOLDABLE_H_