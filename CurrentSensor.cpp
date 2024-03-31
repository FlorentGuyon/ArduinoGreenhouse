/**
  * @file     CurrentSensor.cpp
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the CurrentSensor functions
  *
  **/
  
#include "CurrentSensor.h"  // Definition of the CurrentSensor class
#include <Arduino.h>

// ############################################################################ CONSTRUCTORS
//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A

CurrentSensor::CurrentSensor(uint8_t sensor_pin, uint8_t minimum_acceptable_milliampere, uint8_t maximum_acceptable_milliampere, uint8_t milliampere_tolerance) : ACS712(sensor_pin, 5.0, 1023, 185) {
  set_sensor_pin(sensor_pin);
  set_milliampere(new SensorValue16Bits());
  get_milliampere()->set_minimum_acceptable(minimum_acceptable_milliampere);
  get_milliampere()->set_maximum_acceptable(maximum_acceptable_milliampere);
  get_milliampere()->set_tolerance(milliampere_tolerance);
}

// ############################################################################ SETTERS

void CurrentSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

void CurrentSensor::set_milliampere(SensorValue16Bits* milliampere) {
  this->_milliampere = milliampere;
}

// ############################################################################ GETTERS

uint8_t CurrentSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

SensorValue16Bits* CurrentSensor::get_milliampere(void) {
  return this->_milliampere;
}

// ############################################################################ FUNCTIONS

void CurrentSensor::initialize(void) {
  ACS712::autoMidPointDC();
}

bool CurrentSensor::read_current(void) {
  // Read the current drawn
  uint16_t current_value = ACS712::mA_DC();
  // If the current value is invalid
  if (!get_milliampere()->validate(current_value)) {
    // Write it in the console
    Serial.print(F("Error: The current is invalid: "));
    Serial.println(current_value);
    // Quit the method with an error code
    return false;
  }
  // Else, quit the method with a success code
  return true;
}