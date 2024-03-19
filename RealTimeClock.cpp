/**cpp
  * @file     RealTimeClock.cpp
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the RealTimeClock functions
  *
  **/

#include "RealTimeClock.h"  // Definition of the RealTimeClock class

// ############################################################################ CONSTRUCTORS

RealTimeClock::RealTimeClock() : DS3231() {
}

RealTimeClock::RealTimeClock(uint8_t I2C_address) : DS3231() {
  set_I2C_address(I2C_address);
}

// ############################################################################ SETTERS

void RealTimeClock::set_I2C_address(uint8_t I2C_address) {
  this->_I2C_address = I2C_address;
}

// ############################################################################ GETTERS

uint8_t RealTimeClock::get_I2C_address(void) {
  return this->_I2C_address;
}

String RealTimeClock::get_timedate(void) {
  //
  bool flag = false;
  //
  return String(DS3231::getYear()) + "-" + 
    String(DS3231::getMonth(flag)) + "-" + 
    String(DS3231::getDate()) + " " +
    String(DS3231::getHour(flag, flag)) + ":" + 
    String(DS3231::getMinute()) + ":" + 
    String(DS3231::getSecond());
}

// ############################################################################ OTHERS

void RealTimeClock::initialize() {
  Wire.begin();
}