/**
  * @file     LCDScreen.cpp
  * @version  V1.0
  * @date     2024, February 23
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LCDScreen functions
  *
  **/

#include "LCDScreen.h"  // Definition of the CurrentSensor class
#include "Arduino.h"    // Definition of the analogRead function

byte char_degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte char_arrow[8] = {
  B10000,
  B10000,
  B10000,
  B10100,
  B10110,
  B11111,
  B00110,
  B00100,
};

// ############################################################################ CONSTRUCTORS

LCDScreen::LCDScreen() {}

LCDScreen::LCDScreen(uint8_t count_columns, uint8_t count_lines) {
  set_count_columns(count_columns);
  set_count_lines(count_lines);
}

// ############################################################################ SETTERS

bool LCDScreen::set_count_columns(uint8_t count_columns) {
  this->_count_columns = count_columns;
  return true;
}

bool LCDScreen::set_count_lines(uint8_t count_lines) {
  this->_count_lines = count_lines;
  return true;
}

// ############################################################################ GETTERS

uint8_t LCDScreen::get_count_columns(void) {
  return this->_count_columns;
}

uint8_t LCDScreen::get_count_lines(void) {
  return this->_count_lines;
}