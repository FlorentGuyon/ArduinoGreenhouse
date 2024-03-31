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

TemperatureSensor::TemperatureSensor(uint8_t sensor_pin, uint8_t minimum_acceptable_temperature, uint8_t maximum_acceptable_temperature, uint8_t temperature_tolerance, uint8_t minimum_acceptable_humidity, uint8_t maximum_acceptable_humidity, uint8_t humidity_tolerance) : AM2302::AM2302_Sensor(sensor_pin) {
  set_sensor_pin(sensor_pin);
  set_ready(false);
  set_temperature(new SensorValue8Bits());
  get_temperature()->set_minimum_acceptable(minimum_acceptable_temperature);
  get_temperature()->set_maximum_acceptable(maximum_acceptable_temperature);
  get_temperature()->set_tolerance(temperature_tolerance);
  set_humidity(new SensorValue8Bits());
  get_humidity()->set_minimum_acceptable(minimum_acceptable_humidity);
  get_humidity()->set_maximum_acceptable(maximum_acceptable_humidity);
  get_humidity()->set_tolerance(humidity_tolerance);
}

// ############################################################################ SETTERS

void TemperatureSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

void TemperatureSensor::set_ready(bool is_ready) {
  this->_is_ready = is_ready;
}

void TemperatureSensor::set_humidity(SensorValue8Bits* humidity) {
  this->_humidity = humidity;
}

void TemperatureSensor::set_temperature(SensorValue8Bits* temperature) {
  this->_temperature = temperature;
}

// ############################################################################ GETTERS

bool TemperatureSensor::is_ready(void) {
  return this->_is_ready;
}

uint8_t TemperatureSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

SensorValue8Bits* TemperatureSensor::get_humidity(void) {
  return this->_humidity;
}

SensorValue8Bits* TemperatureSensor::get_temperature(void) {
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
    Serial.println(F("Error: The temperature sensor is not ready."));
    return false;
  }

  if (AM2302::AM2302_Sensor::read() != AM2302::AM2302_READ_OK) {
    Serial.println(F("Error: The temperature sensor failed to read data."));
    return false;
  }

  if (!get_temperature()->validate(AM2302::AM2302_Sensor::get_Temperature())) {
    Serial.print(F("Error: The temperature is invalid: "));
    Serial.println(AM2302::AM2302_Sensor::get_Temperature());
  }

  if (!get_humidity()->validate(AM2302::AM2302_Sensor::get_Humidity())) {
    Serial.print(F("Error: The humidity is invalid: "));
    Serial.println(AM2302::AM2302_Sensor::get_Humidity());
  }

  return true;
}