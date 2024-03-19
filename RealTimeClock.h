/**
  * @file     RealTimeClock.h
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the RealTimeClock class
  *
  * Real Time Clock GND Pin -> Ground
  * Real Time Clock VCC Pin -> +5V
  * Real Time Clock SDA Pin -> Arduino SDA Pin
  * Real Time Clock SCL Pin -> Arduino SCL Pin
  * Real Time Clock MQW Pin -> Ground
  * Real Time Clock 32K Pin -> Ground
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <Wire.h> // Definition of the I2C functions
#include <DS3231.h> // Definition of the DS3231.h class

#ifndef REALTIMECLOCK_H
#define REALTIMECLOCK_H

class RealTimeClock : public DS3231::DS3231 {

private:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _I2C_address;

public:

  // ########################################################################## CONSTRUCTORS

  RealTimeClock();
  RealTimeClock(uint8_t I2C_address);

  // ########################################################################## SETTERS

  void set_I2C_address(uint8_t I2C_address);

  // ########################################################################## GETTERS

  uint8_t get_I2C_address(void);
  String get_timedate(void);

  // ########################################################################## OTHERS

  void initialize(void);
};

#endif  // REALTIMECLOCK_H