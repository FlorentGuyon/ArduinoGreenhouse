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

  Threshold::Threshold(void* value_address, uint16_t threshold) {
    set_value_address(value_address);
    set_value_size(sizeof(value_address));
    set_threshold(threshold);
  }

// ############################################################################ SETTERS

void Threshold::set_value_address(void* value_address) {
  this->_value_address = value_address;
}

void Threshold::set_value_size(size_t value_size) {
  this->_value_size = value_size;
}

void Threshold::set_threshold(uint16_t threshold) {
  this->_threshold = threshold;
}

// ############################################################################ GETTERS

void* Threshold::get_value_address(void) {
  return this->_value_address;
}

size_t Threshold::get_value_size(void) {
  return this->_value_size;
}

uint16_t Threshold::get_threshold(void) {
  return this->_threshold;
}

// ############################################################################ OTHERS

bool Threshold::is_threshold_reached() {} // virtual

// ############################################################################ MINIMAL THRESHOLD CONSTRUCTORS

MinimalThreshold::MinimalThreshold(void* value_address, uint16_t threshold) : Threshold(value_address, threshold) {}

// ############################################################################ MINIMAL THRESHOLD OTHERS

bool MinimalThreshold::is_threshold_reached() {
  //
  if (get_value_address() == nullptr) {
    Serial.println(F("Unable to check threshold. Value address is null."));
    return false;
  }
  //
  if (get_threshold() == (uint16_t) -1) {
    Serial.println(F("Unable to check threshold. Threshold is null."));
    return false;
  }
  //
  if (get_value_size() == sizeof(uint8_t)) {
    return (*static_cast<uint8_t*>(get_value_address()) < get_threshold());
  } 
  //
  else if (get_value_size() == sizeof(uint16_t)) {
    return (*static_cast<uint16_t*>(get_value_address()) < get_threshold());
  }
}

// ############################################################################ MAXIMAL THRESHOLD CONSTRUCTORS

MaximalThreshold::MaximalThreshold(void* value_address, uint16_t threshold) : Threshold(value_address, threshold) {}

// ############################################################################ MAXIMAL THRESHOLD OTHERS

bool MaximalThreshold::is_threshold_reached() {
  if (get_value_address() == nullptr) {
    Serial.println(F("Unable to check threshold. Value address is null."));
    return false;
  }
  if (get_threshold() == (uint16_t) -1) {
    Serial.println(F("Unable to check threshold. Threshold is null."));
    return false;
  }
  //
  if (get_value_size() == sizeof(uint8_t)) {
    return (*static_cast<uint8_t*>(get_value_address()) > get_threshold());
  } 
  //
  else if (get_value_size() == sizeof(uint16_t)) {
    return (*static_cast<uint16_t*>(get_value_address()) > get_threshold());
  }
}
