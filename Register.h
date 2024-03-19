/**
  * @file     Register.h
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Register class
  *
  * Register VCC Pin -> +5V
  * Register SER Pin -> Arduino Digital 2 Pin
  * Register RCK Pin -> Arduino Digital 3 Pin
  * Register SCK Pin -> Arduino PWM 4 Pin
  * Register  QA Pin -> Relay 1 Gate Pin
  * Register  QB Pin -> Relay 2 Gate Pin
  * Register  QC Pin -> Relay 3 Gate Pin
  * Register  QD Pin -> Relay 4 Gate Pin
  * Register  QE Pin -> Relay 5 Gate Pin
  * Register  QF Pin -> Relay 6 Gate Pin
  * Register  QG Pin -> Relay 7 Gate Pin
  * Register  QH Pin -> Relay 8 Gate Pin
  * Register  OE Pin -> +5V
  * Register CLR Pin -> +5V
  * Register QH' Pin -> ?
  * Register GND Pin -> Ground
  *
  **/

#ifndef REGISTER_H
#define REGISTER_H

#include <Arduino.h> // Definition of the OUTPUT macro
#include <stdint.h> // Definition of the uint8_t type
#include "Switchable.h" // Definition of the Switchable class

class Register {

private:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _SER_pin; // Serial data input
  uint8_t _RCK_pin; // Storage register clock
  uint8_t _SCK_pin; // Serial clock

  // DATA
  bool** _switches;
  uint8_t _count_switches; // Number of shift registers daisy-chained

public:

  // ########################################################################## CONSTRUCTORS

  Register(uint8_t SER_pin, uint8_t RCK_pin, uint8_t SCK_pin);
  Register(uint8_t SER_pin, uint8_t RCK_pin, uint8_t SCK_pin, bool** switches, uint8_t count_switches);

  // ########################################################################## SETTERS

  void set_SER_pin(uint8_t SER_pin);
  void set_RCK_pin(uint8_t RCK_pin);
  void set_SCK_pin(uint8_t SCK_pin);
  void set_switches(bool** switches);
  void set_count_switches(uint8_t count_switches);

  // ########################################################################## GETTERS

  uint8_t get_SER_pin(void);
  uint8_t get_RCK_pin(void);
  uint8_t get_SCK_pin(void);
  bool** get_switches(void);
  uint8_t get_count_switches(void);

  // ########################################################################## OTHERS

  void initialize(void);
  void flush_bits(void);
  void print_bits(void);

};

#endif  // REGISTER_H