/**
  * @file     Pulsable.cpp
  * @version  V1.0
  * @date     2024, March 18
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Pulsable functions
  *
  **/
  
#include <Arduino.h> // Definition of the delay function
#include "Pulsable.h"  // Definition of the Pulsable class

// ############################################################################ CONSTRUCTORS

Pulsable::Pulsable(uint8_t pulse_pin) {
  set_pulse_pin(pulse_pin);
}

// ############################################################################ SETTERS

void Pulsable::set_pulse_pin(uint8_t pulse_pin) {
  this->_pulse_pin = pulse_pin;
  pinMode(pulse_pin, OUTPUT);
}

// ############################################################################ GETTERS

uint8_t Pulsable::get_pulse_pin() {
  return this->_pulse_pin;
}

// ############################################################################ OTHER

void Pulsable::pulse(uint16_t pulse_duration, uint8_t count_pulses, uint16_t pulses_interval) {
  //
  if (get_pulse_pin() == 65535) {
    Serial.println(F("Unable to use the pulsable without a pin."));
    return;
  }
  //
  for (uint8_t i = 1 ; i <= count_pulses; i++) {
    digitalWrite(get_pulse_pin(), HIGH);
    delay(pulse_duration);
    digitalWrite(get_pulse_pin(), LOW);
    delay(pulses_interval);
  }
}