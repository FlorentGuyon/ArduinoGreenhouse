/**cpp
  * @file     LCDScreenWithI2C.cpp
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LCDScreenWithI2C functions
  *
  **/

#include "LCDScreenWithI2C.h"  // Definition of the LCDScreenWithI2C class

// ############################################################################ CONSTRUCTORS

LCDScreenWithI2C::LCDScreenWithI2C(uint8_t I2C_address, uint8_t count_columns, uint8_t count_lines) : LCDScreen(count_columns, count_lines), LiquidCrystal_I2C(I2C_address, count_columns, count_lines) {
  set_I2C_address(I2C_address);
}

// ############################################################################ SETTERS

bool LCDScreenWithI2C::set_I2C_address(uint8_t I2C_address) {
  this->_I2C_address = I2C_address;
  return true;
}

// ############################################################################ GETTERS

uint8_t LCDScreenWithI2C::get_I2C_address(void) {
  return this->_I2C_address;
}

// ############################################################################ OTHERS

void LCDScreenWithI2C::initialize() {
  LiquidCrystal_I2C::init();
}

void LCDScreenWithI2C::write_text(const char* text) {
  LiquidCrystal_I2C::clear();
  LiquidCrystal_I2C::setCursor(0, 0);
  LiquidCrystal_I2C::print(text);
  LiquidCrystal_I2C::backlight();
}