/**
  * @file     SoilHumiditySensor.cpp
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SoilHumiditySensor functions
  *
  **/
  
#include <Arduino.h> // Definition of the analogRead function
#include "SoilHumiditySensor.h"  // Definition of the SoilHumiditySensor class

#define minimal_analog_value 280 // /1023 (in water)
#define maximal_analog_value 930 // /1023 (in air)

// ############################################################################ CONSTRUCTORS

SoilHumiditySensor::SoilHumiditySensor(uint8_t sensor_pin, uint8_t minimum_acceptable_humidity, uint8_t maximum_acceptable_humidity, uint8_t humidity_tolerance) {
  set_sensor_pin(sensor_pin);
  set_humidity(new SensorValue8Bits());
  get_humidity()->set_minimum_acceptable(minimum_acceptable_humidity);
  get_humidity()->set_maximum_acceptable(maximum_acceptable_humidity);
  get_humidity()->set_tolerance(humidity_tolerance);
}

// ############################################################################ SETTERS

void SoilHumiditySensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

void SoilHumiditySensor::set_humidity(SensorValue8Bits* humidity) {
  this->_humidity = humidity;
}

// ############################################################################ GETTERS

uint8_t SoilHumiditySensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

SensorValue8Bits* SoilHumiditySensor::get_humidity(void) {
  return this->_humidity;
}

// ############################################################################ OTHER

bool SoilHumiditySensor::read_data(void) {
  // Read the humidity
  uint16_t analogValue = analogRead(get_sensor_pin());
  // If the value is less than the minimal expected
  if (analogValue < minimal_analog_value) {
    // Set the value to the minimum expected
    analogValue = minimal_analog_value;
  }
  // Else, if the value is more than the maximum expected
  else if (analogValue > maximal_analog_value) {
    // Set the value to the maximum expected
    analogValue = maximal_analog_value;
  }
  // Map the corrected analog value with a scale of 0% to 100%
  // And reverse it, as the analog value decrease when the soil humidity increase
  uint8_t humidity = 100 - map(analogValue, minimal_analog_value, maximal_analog_value, 0, 100);
  // If the current value is invalid
  if (!get_humidity()->validate(humidity)) {
    // Write it in the console
    Serial.print(F("Error: The humidity is invalid: "));
    Serial.println(humidity);
    // Quit the method with an error code
    return false;
  }
  // Else, quit the method with a success code
  return true;
}