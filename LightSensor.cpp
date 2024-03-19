/**
  * @file     LightSensor.cpp
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LightSensor functions
  *
  **/
  
#include "LightSensor.h" // Definition of the LightSensor class
#include "Arduino.h" // Definition of the analogRead function

// ############################################################################ CONSTRUCTORS

LightSensor::LightSensor(uint8_t resistance_pin) {
  set_resistance_pin(resistance_pin);
  set_illuminance(0);
}

// ############################################################################ SETTERS

void LightSensor::set_resistance_pin(uint8_t resistance_pin) {
  this->_resistance_pin = resistance_pin;
  pinMode(resistance_pin, INPUT);
}

void LightSensor::set_illuminance(uint16_t illuminance) {
  this->_illuminance = illuminance;
}

// ############################################################################ GETTERS

uint8_t LightSensor::get_resistance_pin() {
    return this->_resistance_pin;
}
uint16_t LightSensor::get_illuminance() {
    return this->_illuminance;
}

// ############################################################################ OTHER

void LightSensor::read_illuminance() {
  uint16_t resistance = analogRead(get_resistance_pin());

  // Linear :
  // Define the minimal and maximal values of the resistance and illuminance
  //uint8_t minimal_input = 0;
  //uint16_t maximal_input = 1023;
  //uint8_t minimal_output = 10; // lux
  //uint16_t maximal_output = 10000; // lux

  // Map the resistance value on the relationship betwwen resistance and illuminance
  //uint16_t illuminance = (resistance - minimal_input) * (maximal_output - minimal_output) / (maximal_input - minimal_input) + minimal_output;
  
  uint16_t illuminance = 0;

  if (resistance < 21) {
    illuminance = 1;
  } else if (resistance < 103) {
    illuminance = 10;
  } else if (resistance < 410) {
    illuminance = 100;
  } else if (resistance < 778) {
    illuminance = 1000;
  } else {
    illuminance = 1000;
  }

  Serial.print("Resistance: ");
  Serial.println(resistance);
  Serial.print("Illuminance: ");
  Serial.println(illuminance);
  
  // Logarithmic :
  //
  // R is the resistance in ohms
  // E is the illuminance in lux
  // A is a manufacturer constant
  // alpha is a manufacturer constant, generally between 0.7 and 0.9
  //
  // R = A(E^-a)
  // E = (R/A)^(-1/a)
  //
  //uint16_t illuminance = pow((resistance / 450), (-1.0 / 0.8));

  set_illuminance(resistance);
}