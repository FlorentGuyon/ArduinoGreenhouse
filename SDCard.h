/**
  * @file     SDCard.h
  * @version  V1.0
  * @date     2024, Marcch 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SDCard class
  *
  * SD Card Gnd  Pin -> Ground
  * SD Card VCC  Pin -> +5V
  * SD Card MISO Pin -> Arduino Digital 12 Pin
  * SD Card MOSI Pin -> Arduino PWM 11 Pin
  * SD Card SCK  Pin -> Arduino Digital 13 Pin
  * SD Card CS   Pin -> Arduino PWM 10 Pin
  *
  * Datasheet : 
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <SD.h>
#include <SPI.h>

#ifndef _SDCARD_H_
#define _SDCARD_H_

class SDCard {

private:

  // ########################################################################## ATTRIBUTES

  // PIN
  uint8_t _CS_pin;
  
  // DATA
  bool _is_ready;

public:

  // ########################################################################## CONSTRUCTORS

  SDCard(uint8_t CS_pin);

  // ########################################################################## SETTERS

  void set_CS_pin(uint8_t CS_pin);
  void set_is_ready(bool is_ready);

  // ########################################################################## GETTERS

  uint8_t get_CS_pin(void);
  bool is_ready(void);

  // ########################################################################## OTHERS

  bool initialize(void);
  bool write(char* fileName, String text);
};

#endif // _SDCARD_H_
