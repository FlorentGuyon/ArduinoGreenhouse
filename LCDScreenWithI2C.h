/**
  * @file     LCDScreenWithI2C.h
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LCDScreenWithI2C class
  *
  * I2C GND Pin -> Ground
  * I2C VCC Pin -> +5V
  * I2C SDA Pin -> Arduino SDA Pin
  * I2C SCL Pin -> Arduino SCL Pin
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <LiquidCrystal_I2C.h> // Definition of the LiquidCrystal_I2C class
#include "LCDScreen.h" // Definition of the LCDScreen class

#ifndef LCDSCREENWITH_H
#define LCDSCREENWITH_H

class LCDScreenWithI2C : public LCDScreen::LCDScreen, public LiquidCrystal_I2C::LiquidCrystal_I2C {

private:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _I2C_address;

public:

  // ########################################################################## CONSTRUCTORS

  LCDScreenWithI2C(uint8_t I2C_address,
                  uint8_t count_columns,
                  uint8_t count_lines);

  // ########################################################################## SETTERS

  bool set_I2C_address(uint8_t I2C_address);

  // ########################################################################## GETTERS

  uint8_t get_I2C_address(void);

  // ########################################################################## OTHERS

  void initialize(void);
  void write_text(const char* text);
  void write_text(const String text);
};

#endif  // LCDSCREENWITH_H