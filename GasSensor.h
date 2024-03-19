/**
  * @file     humiditySensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the humiditySensor class
  *
  * MQ135 DOUT Pin -> None (is high when the gas concentration threshold is reached)
  * MQ135 AOUT Pin -> Arduino Analog A3 Pin (Gas)
  * MQ135 Gnd  Pin -> Ground
  * MQ135 VCC  Pin -> +5V
  *
  * Datasheet : https://www.olimex.com/Products/Components/Sensors/Gas/SNS-MQ135/resources/SNS-MQ135.pdf
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <MQ135.h> // Definition of the MQ135 class

#ifndef GASSENSOR_H
#define GASSENSOR_H

/**
  * -----------------------------
  * | GAS     | PARA   | PARB   |
  * |---------|--------|--------|
  * | CO      | 605.18 | -3.937 |  
  * | Alcohol | 77.255 | -3.180 | 
  * | CO2     | 110.47 | -2.862 |
  * | Toluen  | 44.947 | -3.445 |
  * | NH4     | 102.20 | -2.473 |
  * | Aceton  | 34.668 | -3.369 |
  * -----------------------------
  */

#define PARA 110.47 // CO2
#define PARB -2.862 // CO2

class GasSensor : public MQ135::MQ135 {

public:

  // ########################################################################## ATTRIBUTES

  // PINS
  uint8_t _sensor_pin; // Analog input

  // DATA
  uint8_t _humidity; // 30.00%
  uint8_t _temperature; // 20.00°C
  uint16_t _gas_concentration; // 600ppm

  // ########################################################################## CONSTRUCTORS

  GasSensor(uint8_t sensor_pin);

  // ########################################################################## SETTERS

  void set_sensor_pin(uint8_t sensor_pin);
  bool set_humidity(uint8_t humidity);
  bool set_temperature(uint8_t temperature);
  bool set_gas_concentration(uint16_t gas_concentration);

  // ########################################################################## GETTERS

  uint8_t get_sensor_pin(void);
  uint8_t get_humidity(void);
  uint8_t get_temperature(void);
  uint16_t get_gas_concentration(void);

  // ########################################################################## OTHER

  bool read_data(void);
};

#endif  // GASSENSOR_H