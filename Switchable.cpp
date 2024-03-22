/**
  * @file     Switchable.cpp
  * @version  V1.0
  * @date     2024, February 26
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Switchable functions
  *
  **/
  
#include <Arduino.h>    // Definition of the digitalWrite function
#include "Switchable.h" // Definition of the Switchable class

// ############################################################################ CONSTRUCTORS

Switchable::Switchable(uint8_t switch_pin, Threshold** thresholds = nullptr, uint8_t count_thresholds = 0) : Thresholdable(thresholds, count_thresholds) {
  set_switch_pin(switch_pin);
  set_switch_value(false);
}

// ############################################################################ SETTERS

void Switchable::set_switch_pin(uint8_t switch_pin) {
  this->_switch_pin = switch_pin;
  pinMode(switch_pin, OUTPUT);
}

bool Switchable::set_switch_value(bool switch_value) {
  if ((switch_value < 0) || (switch_value > 1)) {
    Serial.print(F("Unable to set the value \""));
    Serial.print(switch_value);
    Serial.println(F("\" to a switch."));
    return false;
  }
  this->_switch_value = switch_value;
}

// ############################################################################ GETTERS

uint8_t Switchable::get_switch_pin() {
  return this->_switch_pin;
}

bool Switchable::get_switch_value() {
  return this->_switch_value;
}

// ############################################################################ OTHER

void Switchable::turn_switch_on() {
  // If the switch pin is set
  if (get_switch_pin() != (uint8_t) -1) {
    // Send it a high signal
	  digitalWrite(get_switch_pin(), HIGH);
  }
  // Save the new value
  set_switch_value(true);
}

void Switchable::turn_switch_off() {
  // If the switch pin is set
  if (get_switch_pin() != (uint8_t) -1) {
    // Send it a low signal
	  digitalWrite(get_switch_pin(), LOW);
  }
  // Save the new value
  set_switch_value(false);
}

void Switchable::toggle_switch() {
  // If the switch is on
  if (get_switch_value()) {
    // turn it off
    turn_switch_off();
  }
  // Else, if the switch is off
  else {
    // Turn it on
    turn_switch_on();
  }
}

void Switchable::check_thresholds() {
  // If at least one threshold is reached
  if (Thresholdable::are_thresholds_reached()) {
    // Turn the switch on
    turn_switch_on();
  } 
  // Else, if no threshold is reached
  else {
    // Turn the switch off
    turn_switch_off();
  }
}