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

LightSensor::LightSensor(uint8_t I2C_address, uint8_t minimum_acceptable_illuminance = 0, uint8_t maximum_acceptable_illuminance = 10000, uint8_t illuminance_tolerance = 10000) : BH1750(I2C_address) {
  set_I2C_address(I2C_address);
  set_illuminance(new SensorValue16Bits());
  get_illuminance()->set_minimum_acceptable(minimum_acceptable_illuminance);
  get_illuminance()->set_maximum_acceptable(maximum_acceptable_illuminance);
  get_illuminance()->set_tolerance(illuminance_tolerance);
}

// ############################################################################ SETTERS

void LightSensor::set_I2C_address(uint8_t I2C_address) {
  this->_I2C_address = I2C_address;
}

void LightSensor::set_illuminance(SensorValue16Bits* illuminance) {
  this->_illuminance = illuminance;
}

// ############################################################################ GETTERS

uint8_t LightSensor::get_I2C_address(void) {
    return this->_I2C_address;
}

SensorValue16Bits* LightSensor::get_illuminance(void) {
    return this->_illuminance;
}

bool LightSensor::is_ready(void) {
  return this->_is_ready;
}

// ############################################################################ OTHER

bool LightSensor::initialize(void) {
  // Initialize the I2C bus 
  Wire.begin();
  // Try to initiate the communication with the BH1750 module
  if (!BH1750::begin(ONE_TIME_HIGH_RES_MODE, get_I2C_address())) {
    // If it fails, write it in the console
    Serial.println(F("Unable to initialize the light sensor"));
    // Quit the function with an error code
    return false;
  }
  // Quit the function with a success code
  return true;
} 

bool LightSensor::read_illuminance(void) {
  // If the light sensor module is not initialized
  if (!is_ready()) {
    // If the light sensor module fail to be initialized
    if (!initialize()) {
      // Quit the function
      Serial.println(F("Unable to read the illuminance."));
      // Quit the function with an error code
      return false;
    }
  }
  // Configure the module for a new "on time" read
  BH1750::configure(BH1750::ONE_TIME_HIGH_RES_MODE);
  // Wait for the module to be ready to read the soil humidity
  while (!BH1750::measurementReady());
  // Try to read the illuminance
  uint16_t illuminance = BH1750::readLightLevel();
  // If the current value is invalid
  if (!get_illuminance()->validate(illuminance)) {
    // Write it in the console
    Serial.print(F("Error: The illuminance is invalid: "));
    Serial.println(illuminance);
    // Quit the method with an error code
    return false;
  }
  // Else, quit the method with a success code
  return true;
}