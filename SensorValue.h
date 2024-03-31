/**
  * @file     SensorValue.h
  * @version  V1.0
  * @date     2024, March 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SensorValue class
  *
  **/

#include <stdint.h> // Definition of the uint8_t type

#ifndef SENSORVALUE_H
#define SENSORVALUE_H

class SensorValue {

public:

  // ########################################################################## ATTRIBUTES

  // DATA
  uint8_t _count_readings; // Example: 2 (Increase of 1 each time a value is read and validated)
  
  // ########################################################################## CONSTRUCTORS

  SensorValue();

  // ########################################################################## SETTERS

  void set_count_readings(uint8_t count_readings);

  // ########################################################################## GETTERS

  uint8_t get_count_readings(void);
};

class SensorValue8Bits : public SensorValue {

public:

  // ########################################################################## ATTRIBUTES

  // DATA
  uint8_t _value;               // Example: 21°C (Last value read and validated)
  uint8_t _last_value;          // Example: 23°C (value read and validated before the current one)
  uint8_t _minimum_acceptable;  // Example:  5°C (A read value lower than this minimum will be ignored)
  uint8_t _maximum_acceptable;  // Example: 35°C (A read value higher than this maximum will be ignored)
  uint8_t _tolerance;           // Example:  4°C (A read value lower or higher of this tolerance, compared to the previous validated valued, will be ignored)
  uint8_t _average;             // Example: 22°C (Average of all the validated values)

  // ########################################################################## CONSTRUCTORS

  SensorValue8Bits(uint8_t minimum_acceptable = 0, uint8_t maximum_acceptable = (uint8_t) -1, uint8_t tolerance = (uint8_t) -1);

  // ########################################################################## SETTERS

  void set_value(uint8_t value);
  void set_last_value(uint8_t last_value);
  void set_minimum_acceptable(uint8_t minimum_acceptable);
  void set_maximum_acceptable(uint8_t maximum_acceptable);
  void set_tolerance(uint8_t tolerance);
  void set_average(uint8_t average);

  // ########################################################################## GETTERS

  uint8_t get_value(void);
  uint8_t get_last_value(void);
  uint8_t get_minimum_acceptable(void);
  uint8_t get_maximum_acceptable(void);
  uint8_t get_tolerance(void);
  uint8_t get_count_readings(void);
  uint8_t get_average(void);

  // ########################################################################## OTHERS

  void reset_average(void);
  bool validate(uint8_t new_value);
};

class SensorValue16Bits : public SensorValue {

public:

  // ########################################################################## ATTRIBUTES

  // DATA
  uint16_t _value;               // Example: 21°C (Last value read and validated)
  uint16_t _last_value;          // Example: 23°C (value read and validated before the current one)
  uint16_t _minimum_acceptable;  // Example:  5°C (A read value lower than this minimum will be ignored)
  uint16_t _maximum_acceptable;  // Example: 35°C (A read value higher than this maximum will be ignored)
  uint16_t _tolerance;           // Example:  4°C (A read value lower or higher of this tolerance, compared to the previous validated valued, will be ignored)
  uint16_t _average;             // Example: 22°C (Average of all the validated values)

  // ########################################################################## CONSTRUCTORS

  SensorValue16Bits(uint16_t minimum_acceptable = 0, uint16_t maximum_acceptable = (uint16_t) -1, uint16_t tolerance = (uint16_t) -1);

  // ########################################################################## SETTERS

  void set_value(uint16_t value);
  void set_last_value(uint16_t last_value);
  void set_minimum_acceptable(uint16_t minimum_acceptable);
  void set_maximum_acceptable(uint16_t maximum_acceptable);
  void set_tolerance(uint16_t tolerance);
  void set_average(uint16_t average);

  // ########################################################################## GETTERS

  uint16_t get_value(void);
  uint16_t get_last_value(void);
  uint16_t get_minimum_acceptable(void);
  uint16_t get_maximum_acceptable(void);
  uint16_t get_tolerance(void);
  uint16_t get_average(void);

  // ########################################################################## OTHERS

  void reset_average(void);
  bool validate(uint16_t new_value);
};

#endif  // SENSORVALUE_H