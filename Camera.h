/**
  * @file     Camera.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the Camera class
  *
  **/

#include <stdint.h> // Definition of the uint8_t type
#include <SD.h>
#include <SPI.h>

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Camera(uint8_t csPin, uint8_t resetPin);
    bool initialize();
    bool captureAndSave(const char* filename);
    
private:
    uint8_t _csPin;
    uint8_t _resetPin;
    
    void resetOV7670();
    bool configureOV7670();
    bool startCapture();
    bool waitForVSYNC();
    void select();
    void deselect();
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
};

#endif  // CAMERA_H