/**
  * @file     Threshold.cpp
  * @version  V1.0
  * @date     2024, March 17
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Threshold functions
  *
  **/
  
#include <Arduino.h> // Definition of Serial
#include "Threshold.h" // Definition of the Threshold class

  // ########################################################################## CONSTRUCTORS

  Threshold::Threshold(uint8_t* value_address, uint16_t threshold) {
    set_value_address(value_address);
    set_threshold(threshold);
  }

// ############################################################################ SETTERS

void Threshold::set_value_address(uint8_t* value_address) {
  this->_value_address = value_address;
}

void Threshold::set_threshold(uint16_t threshold) {
  this->_threshold = threshold;
}

// ############################################################################ GETTERS

uint8_t* Threshold::get_value_address(void) {
  return this->_value_address;
}

uint16_t Threshold::get_threshold(void) {
  return this->_threshold;
}

// ############################################################################ OTHERS

bool Threshold::is_threshold_reached() {} // virtual

// ############################################################################ MINIMAL THRESHOLD CONSTRUCTORS

MinimalThreshold::MinimalThreshold(uint8_t* value_address, uint16_t threshold) : Threshold(value_address, threshold) {}

MinimalThreshold::MinimalThreshold(uint16_t* value_address, uint16_t threshold) : Threshold(reinterpret_cast<uint8_t*>(value_address), threshold) {}

// ############################################################################ MINIMAL THRESHOLD OTHERS

bool MinimalThreshold::is_threshold_reached() {
  if (get_value_address() == nullptr) {
    Serial.println(F("Unable to check threshold. Value address is null."));
    return false;
  }
  if (get_threshold() == 65535) {
    Serial.println(F("Unable to check threshold. Threshold is null."));
    return false;
  }
  return (*get_value_address() < get_threshold());
}

// ############################################################################ MAXIMAL THRESHOLD CONSTRUCTORS

MaximalThreshold::MaximalThreshold(uint8_t* value_address, uint16_t threshold) : Threshold(value_address, threshold) {}

MaximalThreshold::MaximalThreshold(uint16_t* value_address, uint16_t threshold) : Threshold(reinterpret_cast<uint8_t*>(value_address), threshold) {}

// ############################################################################ MAXIMAL THRESHOLD OTHERS

bool MaximalThreshold::is_threshold_reached() {
  if (get_value_address() == nullptr) {
    Serial.println(F("Unable to check threshold. Value address is null."));
    return false;
  }
  if (get_threshold() == 65535) {
    Serial.println(F("Unable to check threshold. Threshold is null."));
    return false;
  }
  return (*get_value_address() > get_threshold());
}
