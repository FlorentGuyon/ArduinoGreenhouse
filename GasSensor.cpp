/**
  * @file     GasSensor.cpp
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the GasSensor functions
  *
  **/
  
#include "GasSensor.h"  // Definition of the GasSensor class

// ############################################################################ CONSTRUCTORS

// float _rzero = Calibration resistance at atmospheric CO2 level (read with MQ135::getCorrectedRZero(temperature, humidity) after 48h outside)
// float _rload = The load resistance on the board in kOhm (read in the getCorrectedPPM function, can be ignored)
GasSensor::GasSensor(uint8_t sensor_pin) : MQ135::MQ135(sensor_pin, 76.63, 10.0) {
  set_sensor_pin(sensor_pin);
  set_humidity(0);
  set_temperature(0);
  set_gas_concentration(0);
}

// ############################################################################ SETTERS

void GasSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

bool GasSensor::set_humidity(uint8_t humidity) {
  this->_humidity = humidity;
  return true;
}

bool GasSensor::set_temperature(uint8_t temperature) {
  this->_temperature = temperature;
  return true;
}

bool GasSensor::set_gas_concentration(uint16_t gas_concentration) {
  this->_gas_concentration = gas_concentration;
  return true;
}

// ############################################################################ GETTERS

uint8_t GasSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

uint8_t GasSensor::get_humidity(void) {
  return this->_humidity;
}

uint8_t GasSensor::get_temperature(void) {
  return this->_temperature;
}

uint16_t GasSensor::get_gas_concentration(void) {
  return this->_gas_concentration;
}

// ############################################################################ OTHER

// A normal CO2 concentration inside would be around 400ppm
bool GasSensor::read_data(void) {
  if (get_temperature() && get_humidity()) {
    set_gas_concentration(MQ135::getCorrectedPPM(get_temperature(),get_humidity()));
  } else {
    set_gas_concentration(MQ135::getPPM());
  }
  //Serial.print("r0: ");
  //Serial.println(MQ135::getCorrectedRZero(get_temperature(),get_humidity()));
  return true;
}