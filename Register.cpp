/**
  * @file     Register.cpp
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Register functions
  *
  **/

#include "Register.h" // Definition of the Register class

// ############################################################################ CONSTRUCTORS

Register::Register(uint8_t SER_pin, uint8_t RCK_pin, uint8_t SCK_pin) {
  set_SER_pin(SER_pin);
  set_RCK_pin(RCK_pin);
  set_SCK_pin(SCK_pin);
  set_count_switches(0);
}

Register::Register(uint8_t SER_pin, uint8_t RCK_pin, uint8_t SCK_pin, bool** switches, uint8_t count_switches) {
  set_SER_pin(SER_pin);
  set_RCK_pin(RCK_pin);
  set_SCK_pin(SCK_pin);
  set_switches(switches);
  set_count_switches(count_switches);
}

// ############################################################################ SETTERS

void Register::set_SER_pin(uint8_t SER_pin) {
  this->_SER_pin = SER_pin;
}

void Register::set_RCK_pin(uint8_t RCK_pin) {
  this->_RCK_pin = RCK_pin;
}

void Register::set_SCK_pin(uint8_t SCK_pin) {
  this->_SCK_pin = SCK_pin;
}

void Register::set_switches(bool** switches) {
  this->_switches = switches;
}

void Register::set_count_switches(uint8_t count_switches) {
  this->_count_switches = count_switches;
}

// ############################################################################ GETTERS

uint8_t Register::get_SER_pin(void) {
  return this->_SER_pin;
}

uint8_t Register::get_RCK_pin(void) {
  return this->_RCK_pin;
}

uint8_t Register::get_SCK_pin(void) {
  return this->_SCK_pin;
}

bool** Register::get_switches(void) {
  return this->_switches;
}

uint8_t Register::get_count_switches(void) {
  return this->_count_switches;
}

// ############################################################################ OTHER

void Register::initialize() {
  // Initialize the shift register pins as outputs
  pinMode(get_SER_pin(), OUTPUT);
  pinMode(get_RCK_pin(), OUTPUT);
  pinMode(get_SCK_pin(), OUTPUT);
}


// Function to print the content of the registers array
void Register::print_bits() {
  for (int bit_index = get_count_switches() -1; bit_index >= 0; bit_index--) {
    // Add the value of the current bit of the current register to the line
    Serial.print(*get_switches()[bit_index]);
  }
  // Print the line to the console
  Serial.println();
}

// Function to write the contents of the registers to the shift registers
void Register::flush_bits() {
  // Start data transfer
  digitalWrite(get_RCK_pin(), LOW); 
  //
  uint8_t bits_shifted = 0;
  //
  byte byte_to_shift = 0;
  //
  for (int switches_index = get_count_switches() - 1; switches_index >= 0; switches_index--) {
    //
    if (*get_switches()[switches_index]) {
      byte_to_shift |= (1 << bits_shifted);
    }
    //
    ++bits_shifted;
    //
    if (bits_shifted == 8) {
      // Send the value of the register to the IC
      shiftOut(get_SER_pin(), get_SCK_pin(), LSBFIRST, byte_to_shift);
      byte_to_shift = 0;
      bits_shifted = 0;
    }
  }
  // End data transfer, latch the data to the outputs
  digitalWrite(get_RCK_pin(), HIGH); 
}