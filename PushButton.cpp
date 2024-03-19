/**
  * @file     PushButton.cpp
  * @version  V1.0
  * @date     2024, March 15
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the PushButton functions
  *
  **/

#include <Arduino.h> // Definition of the digitalRead function
#include "PushButton.h"  // Definition of the CurrentSensor class

// ############################################################################ CONSTRUCTORS

PushButton::PushButton(uint8_t push_pin) {
  set_push_pin(push_pin);
  set_last_push_timestamp(0);
  set_last_push_duration(0);
  set_count_pushes(0);
}

// ############################################################################ SETTERS

void PushButton::set_push_pin(uint8_t push_pin) {
  this->_push_pin = push_pin;
}

void PushButton::set_last_push_timestamp(uint32_t last_push_timestamp) {
  this->_last_push_timestamp = last_push_timestamp;
}

void PushButton::set_last_push_duration(uint16_t last_push_duration) {
  this->_last_push_duration = last_push_duration;
}

void PushButton::set_count_pushes(uint8_t count_pushes) {
  this->_count_pushes = count_pushes;
}

// ############################################################################ GETTERS

uint8_t PushButton::get_push_pin(void) {
  return this->_push_pin;
}

uint32_t PushButton::get_last_push_timestamp(void) {
  return this->_last_push_timestamp;
}

uint16_t PushButton::get_last_push_duration(void) {
  return this->_last_push_duration;
}

uint8_t PushButton::get_count_pushes(void) {
  return this->_count_pushes;
}

// ########################################################################## OTHERS

bool PushButton::read_push(uint16_t timeout) {
  if (digitalRead(get_push_pin())) {
    // Get the timestamp of the HIGH signal
    uint32_t start_timestamp = millis();
    // Wail until the LOW signal
    while (digitalRead(get_push_pin())) {
      // If, after the timeout, the signal is still not LOW
      if ((millis() - start_timestamp) >= timeout) {
        // Stop waiting
        break;
      }
    }
    // Set the duration of the last push to the number of milliseconds between the HIGH and the LOW signal
    set_last_push_duration(millis() - start_timestamp);
    set_last_push_timestamp(start_timestamp);
    set_count_pushes(get_count_pushes() +1);
    return true;
  }
  return false;
}