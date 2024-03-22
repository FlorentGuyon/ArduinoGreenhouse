/**
  * @file     Threshold.h
  * @version  V1.0
  * @date     2024, March 17
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Threshold class
  *
  **/

#include <Arduino.h> // Definition of the size_t type
#include <stdint.h> // Definition of the uintX_t types

#ifndef _THRESHOLD_H_
#define _THRESHOLD_H_

class Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  Threshold(void* value_address = nullptr, size_t value_size = sizeof(uint8_t), uint16_t threshold = 0);

  // ########################################################################## ATTRIBUTES

  void* _value_address; // Pointer to the value to check
  size_t _value_size; // Size of the value (8 bits, 16 bits...)
  uint16_t _threshold; // Threshold above/below which the switch value will be set to true

  // ########################################################################## SETTERS
  
  void set_value_address(void* value_address);
  void set_value_size(size_t value_size);
  void set_threshold(uint16_t threshold);

  // ########################################################################## GETTERS
  
  void* get_value_address(void);
  size_t get_value_size(void);
  uint16_t get_threshold(void);

  // ########################################################################## OTHERS

  virtual bool is_threshold_reached(void);
};





class MinimalThreshold : public Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  MinimalThreshold(void* value_address = nullptr, size_t value_size = sizeof(uint8_t), uint16_t threshold = (uint16_t) -1);

  // ########################################################################## OTHERS
  
  bool is_threshold_reached(void) override;
};




class MaximalThreshold : public Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  MaximalThreshold(void* value_address = nullptr, size_t value_size = sizeof(uint8_t), uint16_t threshold = (uint16_t) -1);

  // ########################################################################## OTHERS
  
  bool is_threshold_reached(void) override;
};

#endif  // _THRESHOLD_H_