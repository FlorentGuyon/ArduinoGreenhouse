/**
  * @file     PushButton.h
  * @version  V1.0
  * @date     2024, February 23
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the PushButton class
  *
  * Push Button + Pin -> +5V
  * Push Button - Pin -> Arduino Digital 7 Pin (pulled-down)
  *
  **/
  
#include <stdint.h> // Definition of the uint8_t type
#include "Switchable.h" // Definition of the Switchable class

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

class PushButton {

private:

  // ########################################################################## ATTRIBUTES

  // PIN
  uint8_t _push_pin;

  // DATA
  uint32_t _last_push_timestamp; // timestamp (ms since the Arduino started)
  uint16_t _last_push_duration; // ms (from HIGH to LOw)
  uint8_t _count_pushes;

public:

  // ########################################################################## CONSTRUCTORS

  PushButton(uint8_t push_pin);

  // ########################################################################## SETTERS

  void set_push_pin(uint8_t push_pin);
  void set_last_push_timestamp(uint32_t last_push_timestamp);
  void set_last_push_duration(uint16_t last_push_duration);
  void set_count_pushes(uint8_t count_pushes);

  // ########################################################################## GETTERS

  uint8_t get_push_pin(void);
  uint32_t get_last_push_timestamp(void);
  uint16_t get_last_push_duration(void);
  uint8_t get_count_pushes(void);

  // ########################################################################## OTHERS

  bool read_push(uint16_t timeout = -1);
};

#endif  // PUSHBUTTON_H