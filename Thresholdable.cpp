/**
  * @file     Thresholdable.cpp
  * @version  V1.0
  * @date     2024, February 26
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Thresholdable functions
  *
  **/
  
#include <Arduino.h> // Definition of the digitalWrite function
#include "Thresholdable.h" // Definition of the Thresholdable class

// ############################################################################ CONSTRUCTORS

Thresholdable::Thresholdable(Threshold** thresholds, uint8_t count_thresholds) {
  set_thresholds(thresholds);
  set_count_thresholds(count_thresholds);
}

// ############################################################################ SETTERS

void Thresholdable::set_thresholds(Threshold** thresholds) {
  this->_thresholds = thresholds;
}

void Thresholdable::set_count_thresholds(uint8_t count_thresholds) {
  this->_count_thresholds = count_thresholds;
}

// ############################################################################ GETTERS

Threshold** Thresholdable::get_thresholds(void) {
  return this->_thresholds;
}

Threshold* Thresholdable::get_threshold(uint8_t index) {
  return get_thresholds()[index];
}

uint8_t Thresholdable::get_count_thresholds(void) {
  return this->_count_thresholds;
}

// ############################################################################ OTHERS

// Check if a threshold is reached
bool Thresholdable::are_thresholds_reached(void) {
  // Loop through all the thresholds
  for (uint8_t threshold_index = 0 ; threshold_index <= get_count_thresholds() -1 ; threshold_index++) {
    // If at least one threshold is reached
    if (get_threshold(threshold_index)->is_threshold_reached()) {
      // Quit the function with a positive value
      return true;
    }
  }
  // Quit the function with a negative value
  return false;
}