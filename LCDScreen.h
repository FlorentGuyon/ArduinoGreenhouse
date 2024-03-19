/**
  * @file     LCDScreen.h
  * @version  V1.0
  * @date     2024, February 23
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the LCDScreen class
  *
  **/
  
#include <stdint.h> // Definition of the uint8_t type
#include "Switchable.h" // Definition of the Switchable class

#ifndef LCDSCREEN_H
#define LCDSCREEN_H

class LCDScreen {

private:

  // ########################################################################## ATTRIBUTES

  // DATA
  uint8_t _count_columns; // 16
  uint8_t _count_lines; // 2

public:

  // ########################################################################## CONSTRUCTORS

  LCDScreen();
  LCDScreen(uint8_t count_columns,
            uint8_t count_lines);

  // ########################################################################## SETTERS

  bool set_count_columns(uint8_t count_columns);
  bool set_count_lines(uint8_t count_lines);

  // ########################################################################## GETTERS

  uint8_t get_count_columns(void);
  uint8_t get_count_lines(void);
};

#endif  // LCDSCREEN_H