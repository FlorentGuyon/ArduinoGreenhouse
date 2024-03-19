/**
  * @file     Regulator.cpp
  * @version  V1.0
  * @date     2024, February 26
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Regulator functions
  *
  **/
  
#include <Arduino.h> // Definition of the digitalWrite function
#include "Regulator.h" // Definition of the Regulator class

// ############################################################################ CONSTRUCTORS

Regulator::Regulator() : Switchable() {
  set_count_thresholds(0);
}

Regulator::Regulator(Threshold** thresholds, uint8_t count_thresholds, uint8_t switch_pin) : Switchable(switch_pin) {
  set_thresholds(thresholds);
  set_count_thresholds(count_thresholds);
}

// ############################################################################ SETTERS

void Regulator::set_thresholds(Threshold** thresholds) {
  this->_thresholds = thresholds;
}

void Regulator::set_count_thresholds(uint8_t count_thresholds) {
  this->_count_thresholds = count_thresholds;
}

// ############################################################################ GETTERS

Threshold** Regulator::get_thresholds(void) {
  return this->_thresholds;
}

Threshold* Regulator::get_threshold(uint8_t index) {
  return get_thresholds()[index];
}

uint8_t Regulator::get_count_thresholds(void) {
  return this->_count_thresholds;
}

// ############################################################################ OTHERS

void Regulator::check_thresholds() {
  //
  for (int threshold_index = get_count_thresholds() -1 ; threshold_index >= 0 ; threshold_index--) {
    Switchable::set_switch_value(get_threshold(threshold_index)->is_threshold_reached());  
  }
}