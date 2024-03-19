/**
  * @file     Buzzer.h
  * @version  V1.0
  * @date     2024, February 25
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Buzzer class
  *
  * Buzzer + Pin -> Arduino Digital 8 Pin
  * Buzzer - Pin -> Ground
  *
  **/
  
#include <stdint.h> // Definition of the uint8_t type
#include "Switchable.h" // Definition of the Switchable class

#ifndef BUZZER_H
#define BUZZER_H

class Buzzer : public Switchable::Switchable {
  
public:

  // ########################################################################## CONSTRUCTORS

  Buzzer::Buzzer();
  Buzzer::Buzzer(uint8_t switch_pin);

  // ########################################################################## OTHER

  void buzz(uint16_t milliseconds = 50);
  void buzz(uint16_t milliseconds, uint8_t count_buzzes);
};

#endif  // BUZZER_H