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

CurrentSensor::CurrentSensor(uint8_t sensor_pin) : ACS712(sensor_pin, 5.0, 1023, 185) {
  set_sensor_pin(sensor_pin);
  set_milliampere(0);
}

// ############################################################################ SETTERS

void CurrentSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

void CurrentSensor::set_milliampere(uint8_t milliampere) {
  this->_milliampere = milliampere;
}

// ############################################################################ GETTERS

uint8_t CurrentSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

uint8_t CurrentSensor::get_milliampere(void) {
  return this->_milliampere;
}

// ############################################################################ FUNCTIONS

bool CurrentSensor::initialize(void) {
  ACS712::autoMidPointDC();
}

bool CurrentSensor::read_current(void) {
  set_milliampere(ACS712::mA_DC());
  return true;
}