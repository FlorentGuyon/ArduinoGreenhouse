/**
  * @file     Threshold.h
  * @version  V1.0
  * @date     2024, March 17
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Threshold class
  *
  **/

#include <stdint.h> // Definition of the uintX_t type

#ifndef _THRESHOLD_H_
#define _THRESHOLD_H_

class Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  Threshold(uint8_t* value_address = nullptr, uint16_t threshold = 0);

  // ########################################################################## ATTRIBUTES

  uint8_t* _value_address; // Pointer to the value to check
  uint16_t _threshold; // Threshold above/below which the switch value will be set to true

  // ########################################################################## SETTERS
  
  void set_value_address(uint8_t* value_address);
  void set_threshold(uint16_t threshold);

  // ########################################################################## GETTERS
  
  uint8_t* get_value_address(void);
  uint16_t get_threshold(void);
  virtual bool is_threshold_reached(void);
};





class MinimalThreshold : public Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  MinimalThreshold(uint8_t* value_address = nullptr, uint16_t threshold = 65535);
  MinimalThreshold(uint16_t* value_address = nullptr, uint16_t threshold = 65535);

  // ########################################################################## OTHERS
  
  bool is_threshold_reached(void) override;
};




class MaximalThreshold : public Threshold {

public:

  // ########################################################################## CONSTRUCTORS

  MaximalThreshold(uint8_t* value_address = nullptr, uint16_t threshold = 65535);
  MaximalThreshold(uint16_t* value_address = nullptr, uint16_t threshold = 65535);

  // ########################################################################## OTHERS
  
  bool is_threshold_reached(void) override;
};

#endif  // _THRESHOLD_H_