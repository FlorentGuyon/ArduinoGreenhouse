/**
  * @file     SDCard.cpp
  * @version  V1.0
  * @date     2024, March 13
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the SDCard functions
  *
  **/
  
#include "SDCard.h" // Definition of the SDCard class

// ############################################################################ CONSTRUCTORS

SDCard::SDCard(uint8_t CS_pin) {
  set_CS_pin(CS_pin);
  set_is_ready(false);
}

// ############################################################################ SETTERS

void SDCard::set_CS_pin(uint8_t CS_pin) {
  this->_CS_pin = CS_pin;
}

void SDCard::set_is_ready(bool is_ready) {
  this->_is_ready = is_ready;
}

// ############################################################################ GETTERS

uint8_t SDCard::get_CS_pin() {
  return this->_CS_pin;
}

bool SDCard::is_ready() {
  return this->_is_ready;
}

// ############################################################################ OTHER

bool SDCard::initialize() {
  // If the SD card module can be initialized
  if (SD.begin(get_CS_pin())) {
    // Declare it as ready
    set_is_ready(true);
    return true;
  }
  // Else, if the SD card module fail to be initialized
  else {
    Serial.println(F("Unable to initialize the SD card."));
    return false;
  }
}

bool SDCard::write(char* file_name, String text) {
  // If the SD card module is not initialized
  if (!is_ready()) {
    // If the SD card module fail to be initialized
    if (!initialize()) {
      // Quit the function
      Serial.print(F("Unable to write in the file \""));
      Serial.print(file_name);
      Serial.println(F("\". The SD card module cannot be initialized."));
      return false;
    }
  }

  // Open the file for writing
  File file = SD.open(file_name, FILE_WRITE);

  // If the opening failed
  if (!file) {
    Serial.print(F("Unable to write in the file \""));
    Serial.print(file_name);
    Serial.println(F("\". The file cannot be opened."));
    set_is_ready(false);
    // Quit the function
    return false;
  }

  // If the file is not available for writting
  if (!file.availableForWrite()) {
    Serial.print(F("Unable to write in the file \""));
    Serial.print(file_name);
    Serial.println(F("\". The file is unavailable for writting."));
    // Quit the function
    return false;
  }

  // Write the text in the file
  size_t byte_written = file.print(text);
  // Close the file
  file.close();

  // Return true if the writting succed or false if it failed
  return (byte_written > 0); 
}