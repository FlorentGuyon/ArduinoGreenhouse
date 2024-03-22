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

Pulsable::Pulsable(uint8_t pulse_pin, Threshold** thresholds = nullptr, uint8_t count_thresholds = 0) : Thresholdable(thresholds, count_thresholds) {
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
  // If the pin is unset
  if (get_pulse_pin() == (uint8_t) -1) {
    // Write it in the console
    Serial.println(F("Unable to use the pulsable without a pin."));
    // Quit the function
    return;
  }
  // For each pulse
  for (uint8_t i = 1 ; i <= count_pulses; i++) {
    // Send a high signal to the pin
    digitalWrite(get_pulse_pin(), HIGH);
    // Wait the duration of the pulse
    delay(pulse_duration);
    // Send a low signal to the pin
    digitalWrite(get_pulse_pin(), LOW);
    // If there are more than one pulse
    if (count_pulses > 1) {
      // Wait the duration between two pulses
      delay(pulses_interval);
    }
  }
}

void Pulsable::check_thresholds(uint16_t pulse_duration, uint8_t count_pulses, uint16_t pulses_interval) {
  // If at least one threshold is reached
  if (Thresholdable::are_thresholds_reached()) {
    // Send a pulse
    pulse(pulse_duration, count_pulses, pulses_interval);
  }
}