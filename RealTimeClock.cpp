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

void RealTimeClock::set_is_ready(bool is_ready) {
  this->_is_ready = is_ready;
}

// ############################################################################ GETTERS

uint8_t RealTimeClock::get_I2C_address(void) {
  return this->_I2C_address;
}

bool RealTimeClock::is_ready(void) {
  return this->_is_ready;
}

uint8_t RealTimeClock::get_year(void) {
  return DS3231::getYear();
}

uint8_t RealTimeClock::get_month(void) {
  bool flag = false;
  return DS3231::getMonth(flag);
}

uint8_t RealTimeClock::get_day(void) {
  return DS3231::getDate();
}

uint8_t RealTimeClock::get_hour(void) {
  bool flag = false;
  return DS3231::getHour(flag, flag);
}

uint8_t RealTimeClock::get_minute(void) {
  return DS3231::getMinute();
}

uint8_t RealTimeClock::get_second(void) {
  return DS3231::getSecond();
}

String RealTimeClock::get_timedate(void) {
  return String(get_year()) + "-" + 
    String(get_month()) + "-" + 
    String(get_day()) + " " + 
    String(get_hour()) + ":" + 
    String(get_minute()) + ":" + 
    String(get_second());
}

// ############################################################################ OTHERS

void RealTimeClock::initialize() {
  // Initialize the I2C communication
  Wire.begin();
  // Check if the oscillator is still on (if the time has been kept after power off)
  set_is_ready(DS3231::oscillatorCheck());
  // If not, set the time (local time = true)
  //DS3231::setEpoch(<timestamp>, true);
  // Enable the oscillator (state = true, battery = true, frequency = 1Hz)
  //DS3231::enableOscillator(true, true, 0);
}