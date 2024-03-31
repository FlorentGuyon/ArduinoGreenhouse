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
GasSensor::GasSensor(uint8_t sensor_pin, uint8_t* humidity_address, uint8_t* temperature_address, uint8_t minimum_acceptable_gas_concentration = 0, uint8_t maximum_acceptable_gas_concentration = 2000, uint8_t gas_concentration_tolerance = 2000) : MQ135::MQ135(sensor_pin, 76.63, 10.0) {
  set_sensor_pin(sensor_pin);
  set_humidity_address(humidity_address);
  set_temperature_address(temperature_address);
  set_gas_concentration(new SensorValue16Bits());
  get_gas_concentration()->set_minimum_acceptable(minimum_acceptable_gas_concentration);
  get_gas_concentration()->set_maximum_acceptable(maximum_acceptable_gas_concentration);
  get_gas_concentration()->set_tolerance(gas_concentration_tolerance);
}

// ############################################################################ SETTERS

void GasSensor::set_sensor_pin(uint8_t sensor_pin) {
  this->_sensor_pin = sensor_pin;
  pinMode(sensor_pin, INPUT);
}

bool GasSensor::set_humidity_address(uint8_t* humidity_address) {
  this->_humidity_address = humidity_address;
  return true;
}

bool GasSensor::set_temperature_address(uint8_t* temperature_address) {
  this->_temperature_address = temperature_address;
  return true;
}

bool GasSensor::set_gas_concentration(SensorValue16Bits* gas_concentration) {
  this->_gas_concentration = gas_concentration;
  return true;
}

// ############################################################################ GETTERS

uint8_t GasSensor::get_sensor_pin(void) {
  return this->_sensor_pin;
}

uint8_t* GasSensor::get_humidity_address(void) {
  return this->_humidity_address;
}

uint8_t* GasSensor::get_temperature_address(void) {
  return this->_temperature_address;
}

SensorValue16Bits* GasSensor::get_gas_concentration(void) {
  return this->_gas_concentration;
}

// ############################################################################ OTHER

// A normal CO2 concentration inside would be around 400ppm
bool GasSensor::read_data(void) {
  // If one of the pointer is null
  if ((get_temperature_address() == nullptr) || (get_humidity_address() == nullptr)) {
    // Get a non-corrected gas concentration
    uint16_t gas_concentration = MQ135::getPPM();
    // If the current value is invalid
    if (!get_gas_concentration()->validate(gas_concentration)) {
      // Write it in the console
      Serial.print(F("Error: The gas concentration is invalid: "));
      Serial.println(gas_concentration);
      // Quit the method with an error code
      return false;
    }
    // Else, quit the method with a success code
    return true;
  } 
  // Else, if the pointers are set
  else {
    // Get a corrected gas concentration
    uint16_t gas_concentration = MQ135::getCorrectedPPM(*get_temperature_address(), *get_humidity_address());
    // If the current value is invalid
    if (!get_gas_concentration()->validate(gas_concentration)) {
      // Write it in the console
      Serial.print(F("Error: The gas concentration is invalid: "));
      Serial.println(gas_concentration);
      // Quit the method with an error code
      return false;
    }
    // Else, quit the method with a success code
    return true;
  }
  //Serial.print("r0: ");
  //Serial.println(MQ135::getCorrectedRZero(get_temperature(),get_humidity()));
  return true;
}