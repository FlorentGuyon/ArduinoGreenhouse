/**
  * @file     SensorValue.cpp
  * @version  V1.0
  * @date     2024, March 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SensorValue8Bits functions
  *
  **/

#include "SensorValue.h"  // Definition of the SensorValue class
#include <Arduino.h> // Definition of the abs function

// ########################################################################## CONSTRUCTORS

SensorValue::SensorValue() {}

void SensorValue::set_count_readings(uint8_t count_readings) {
  this->_count_readings = count_readings;
}

uint8_t SensorValue::get_count_readings(void) {
  return this->_count_readings;
}

// ########################################################################## CONSTRUCTORS

SensorValue8Bits::SensorValue8Bits(uint8_t minimum_acceptable, uint8_t maximum_acceptable, uint8_t tolerance) : SensorValue() {
  set_value((uint8_t) -1);
  set_value((uint8_t) -1);
  set_minimum_acceptable(minimum_acceptable);
  set_maximum_acceptable(maximum_acceptable);
  set_tolerance(tolerance);
  reset_average();
}

// ########################################################################## SETTERS

void SensorValue8Bits::set_value(uint8_t value) {
  this->_value = value;
}

void SensorValue8Bits::set_last_value(uint8_t last_value) {
  this->_last_value = last_value;
}

void SensorValue8Bits::set_minimum_acceptable(uint8_t minimum_acceptable) {
  this->_minimum_acceptable = minimum_acceptable;
}

void SensorValue8Bits::set_maximum_acceptable(uint8_t maximum_acceptable) {
  this->_maximum_acceptable = maximum_acceptable;
}

void SensorValue8Bits::set_tolerance(uint8_t tolerance) {
  this->_tolerance = tolerance;
}

void SensorValue8Bits::set_average(uint8_t average) {
  this->_average = average;
}

// ########################################################################## GETTERS

uint8_t SensorValue8Bits::get_value(void) {
  return this->_value;
}

uint8_t SensorValue8Bits::get_last_value(void) {
  return this->_last_value;
}

uint8_t SensorValue8Bits::get_minimum_acceptable(void) {
  return this->_minimum_acceptable;
}

uint8_t SensorValue8Bits::get_maximum_acceptable(void) {
  return this->_maximum_acceptable;
}

uint8_t SensorValue8Bits::get_tolerance(void) {
  return this->_tolerance;
}

uint8_t SensorValue8Bits::get_average(void) {
  return this->_average;
}

// ########################################################################## OTHERS

void SensorValue8Bits::reset_average(void) {
  set_average((uint8_t) -1);
  SensorValue::set_count_readings(0);
}

void SensorValue8Bits::print(void) {
  Serial.print(F("Value: "));
  Serial.print(get_value());
  Serial.print(F(", Average: "));
  Serial.print(get_average());
  Serial.print(F(", Readings: "));
  Serial.print(get_count_readings());
  Serial.print(F(", Minimum: "));
  Serial.print(get_minimum_acceptable());
  Serial.print(F(", Maximum: "));
  Serial.print(get_maximum_acceptable());
  Serial.print(F(", Tolerance: "));
  Serial.println(get_tolerance());
}

bool SensorValue8Bits::validate(uint8_t new_value) {
  // Check if the value is within acceptable range
  if (new_value < get_minimum_acceptable() || new_value > get_maximum_acceptable()) {
    return false;
  }

  // Check if the difference from the last value is within tolerance
  if (SensorValue::get_count_readings() >= 1 && abs(new_value - get_value()) > get_tolerance()) {
    return false;
  }

  // Update value and the last value
  set_last_value(get_value());
  set_value(new_value);

  // Update the average value (cumulative average)
  set_average(((get_average() * SensorValue::get_count_readings()) + new_value) / (SensorValue::get_count_readings() +1));

  // Increment the count of read values
  set_count_readings(SensorValue::get_count_readings() +1);

  return true;
}

// ########################################################################## CONSTRUCTORS

SensorValue16Bits::SensorValue16Bits(uint16_t minimum_acceptable, uint16_t maximum_acceptable, uint16_t tolerance) : SensorValue() {
  set_value((uint16_t) -1);
  set_value((uint16_t) -1);
  set_minimum_acceptable(minimum_acceptable);
  set_maximum_acceptable(maximum_acceptable);
  set_tolerance(tolerance);
  reset_average();
}

// ########################################################################## SETTERS

void SensorValue16Bits::set_value(uint16_t value) {
  this->_value = value;
}

void SensorValue16Bits::set_last_value(uint16_t last_value) {
  this->_last_value = last_value;
}

void SensorValue16Bits::set_minimum_acceptable(uint16_t minimum_acceptable) {
  this->_minimum_acceptable = minimum_acceptable;
}

void SensorValue16Bits::set_maximum_acceptable(uint16_t maximum_acceptable) {
  this->_maximum_acceptable = maximum_acceptable;
}

void SensorValue16Bits::set_tolerance(uint16_t tolerance) {
  this->_tolerance = tolerance;
}

void SensorValue16Bits::set_average(uint16_t average) {
  this->_average = average;
}

// ########################################################################## GETTERS

uint16_t SensorValue16Bits::get_value(void) {
  return this->_value;
}

uint16_t SensorValue16Bits::get_last_value(void) {
  return this->_last_value;
}

uint16_t SensorValue16Bits::get_minimum_acceptable(void) {
  return this->_minimum_acceptable;
}

uint16_t SensorValue16Bits::get_maximum_acceptable(void) {
  return this->_maximum_acceptable;
}

uint16_t SensorValue16Bits::get_tolerance(void) {
  return this->_tolerance;
}

uint16_t SensorValue16Bits::get_average(void) {
  return this->_average;
}

// ########################################################################## OTHERS

void SensorValue16Bits::reset_average(void) {
  set_average((uint16_t) -1);
  SensorValue::set_count_readings(0);
}

void SensorValue16Bits::print(void) {
  Serial.print(F("Value: "));
  Serial.print(get_value());
  Serial.print(F(", Average: "));
  Serial.print(get_average());
  Serial.print(F(", Readings: "));
  Serial.print(get_count_readings());
  Serial.print(F(", Minimum: "));
  Serial.print(get_minimum_acceptable());
  Serial.print(F(", Maximum: "));
  Serial.print(get_maximum_acceptable());
  Serial.print(F(", Tolerance: "));
  Serial.println(get_tolerance());
}

bool SensorValue16Bits::validate(uint16_t new_value) {
  // Check if the value is within acceptable range
  if (new_value < get_minimum_acceptable() || new_value > get_maximum_acceptable()) {
    // Quit the method with an error code
    return false;
  }

  // Check if the difference from the last value is within tolerance
  // int() prevent the unsigned value from being around 65'000 if negative
  if (SensorValue::get_count_readings() >= 1 && abs(int(new_value) - int(get_value())) > get_tolerance()) {
    // Quit the method with an error code
    return false;
  }

  // Update value and the last value
  set_last_value(get_value());
  set_value(new_value);

  // Update the average value (cumulative average)
  set_average(((get_average() * SensorValue::get_count_readings()) + new_value) / (SensorValue::get_count_readings() +1));

  // Increment the count of read values
  set_count_readings(SensorValue::get_count_readings() +1);

  // Quit the method with a success code
  return true;
}
