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

Switchable::Switchable() {
  set_switch_value(false);
}

Switchable::Switchable(uint8_t switch_pin) {
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
	digitalWrite(get_switch_pin(), HIGH);
  set_switch_value(true);
}

void Switchable::turn_switch_off() {
	digitalWrite(get_switch_pin(), LOW);
  set_switch_value(false);
}

void Switchable::toggle_switch_value() {
  digitalWrite(get_switch_pin(), !get_switch_value() ? HIGH : LOW);
  set_switch_value(!get_switch_value());
}
