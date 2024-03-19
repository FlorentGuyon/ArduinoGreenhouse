/**
  * @file     Buzzer.cpp
  * @version  V1.0
  * @date     2024, February 25
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Buzzer functions
  *
  **/
  
#include <Arduino.h> // Definition of the delay function
#include "Buzzer.h"  // Definition of the Buzzer class

// ############################################################################ CONSTRUCTORS

Buzzer::Buzzer() : Switchable::Switchable() {}

Buzzer::Buzzer(uint8_t switch_pin) : Switchable::Switchable(switch_pin) {}

// ############################################################################ OTHER

void Buzzer::buzz(uint16_t milliseconds) {
  Switchable::turn_switch_on();
  delay(milliseconds);
  Switchable::turn_switch_off();
}

void Buzzer::buzz(uint16_t milliseconds, uint8_t count_buzzes) {
  for (uint8_t i = 1 ; i <= count_buzzes; i++) {
    buzz(milliseconds);
    delay(milliseconds);
  }
}