/**
  * @file     TemperatureSensor.cpp
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the TemperatureSensor functions
  *
  **/
  
#include "TemperatureSensor.h"  // Definition of the TemperatureSensor class

// ############################################################################ CONSTRUCTORS

TemperatureSensor::TemperatureSensor(uint8_t sensor_pin) : AM2302::AM2302_Sensor(sensor_pin) {
  set_sensor_pin(sensor_pin);
  set_ready(false);
  set_humidity(0);
  set_temperature(0);
}

// ############################################################################ SETTERS

void TemperatureSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

bool TemperatureSensor::set_ready(bool is_ready) {
  this->_is_ready = is_ready;
  return true;
}

bool TemperatureSensor::set_humidity(uint8_t humidity) {
  this->_humidity = humidity;
  return true;
}

bool TemperatureSensor::set_temperature(uint8_t temperature) {
  this->_temperature = temperature;
  return true;
}

// ############################################################################ GETTERS

bool TemperatureSensor::is_ready(void) {
  return this->_is_ready;
}

uint8_t TemperatureSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

uint8_t TemperatureSensor::get_humidity(void) {
  return this->_humidity;
}

uint8_t TemperatureSensor::get_temperature(void) {
  return this->_temperature;
}

// ############################################################################ OTHER

bool TemperatureSensor::initialize(void) {
  // set pin and check for sensor
  if (!AM2302::AM2302_Sensor::begin()) {
    Serial.println("Error: Failed to initialize the temperature sensor.");
    return false;
  }
  // this delay is needed to receive valid data,
  // when the loop directly read again
  delay(3000);
  set_ready(true);
  return true;
}

bool TemperatureSensor::read_humidity_and_temperature(void) {
  if (!is_ready()) {
    Serial.println("Error: The temperature sensor is not ready.");
    return false;
  }

  if (AM2302::AM2302_Sensor::read() != AM2302::AM2302_READ_OK) {
    Serial.println("Error: The temperature sensor failed to read data.");
    return false;
  }

  if (!set_temperature(AM2302::AM2302_Sensor::get_Temperature())) {
    Serial.println("Error: The temperature sensor failed to save temperature.");
    return false;
  }

  if (!set_humidity(AM2302::AM2302_Sensor::get_Temperature())) {
    Serial.println("Error: The temperature sensor failed to save humidity.");
    return false;
  }

  return true;
}