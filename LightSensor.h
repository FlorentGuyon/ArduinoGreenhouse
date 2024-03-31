/**
  * @file     LightSensor.h
  * @version  V1.0
  * @date     2024, Marcch 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LightSensor class
  *
  * LightSensor GND Pin -> Ground
  * LightSensor VCC Pin -> +5V
  * LightSensor ADD Pin -> Ground
  * LightSensor SDA Pin -> Arduino SDA Pin
  * LightSensor SCL Pin -> Arduino SCL Pin
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include "BH1750.h" // Definition of the BH1750 class
#include "SensorValue.h" // Definition of the SensorValue class

#ifndef _LIGHTSENSOR_H_
#define _LIGHTSENSOR_H_

class LightSensor : public BH1750::BH1750 {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _I2C_address;

  // DATA
  SensorValue16Bits* _illuminance;
  bool _is_ready;
  
  // ########################################################################## CONSTRUCTORS

  LightSensor(uint8_t I2C_address = 0x23, uint8_t minimum_acceptable_illuminance = 0, uint8_t maximum_acceptable_illuminance = 10000, uint8_t illuminance_tolerance = 10000);

  // ########################################################################## SETTERS

  void set_I2C_address(uint8_t I2C_address);
  void set_illuminance(SensorValue16Bits* illuminance);
  void set_is_ready(bool is_ready);

  // ########################################################################## GETTERS
  
  uint8_t get_I2C_address(void);
  SensorValue16Bits* get_illuminance(void);
  bool is_ready(void);
  
  // ########################################################################## OTHERS

  bool initialize(void);
  bool read_illuminance(void);
};

#endif  // _LIGHTSENSOR_H_
