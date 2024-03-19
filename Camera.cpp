#include "Camera.h"

#define OV7670_SLAVE_ADDRESS 0x21
#define OV7670_VSYNC_PIN 2

Camera::Camera(uint8_t csPin, uint8_t resetPin) : _csPin(csPin), _resetPin(resetPin) {}

bool Camera::initialize() {
    pinMode(_csPin, OUTPUT);
    pinMode(_resetPin, OUTPUT);
    deselect();
    resetOV7670();
    return configureOV7670();
}

bool Camera::captureAndSave(const char* filename) {
    if (!startCapture()) {
        return false;
    }
    if (!waitForVSYNC()) {
        return false;
    }
    
    File imageFile = SD.open(filename, FILE_WRITE);
    if (!imageFile) {
        return false;
    }
    
    select();
    SPI.transfer(0x3D); // Start of image data
    for (int i = 0; i < 320 * 240 * 2; i++) {
        uint8_t data = SPI.transfer(0x00);
        imageFile.write(data);
    }
    deselect();
    
    imageFile.close();
    return true;
}

void Camera::resetOV7670() {
    digitalWrite(_resetPin, HIGH);
    delay(10);
    digitalWrite(_resetPin, LOW);
    delay(10);
    digitalWrite(_resetPin, HIGH);
    delay(10);
}

bool Camera::configureOV7670() {
    // Configure OV7670 registers for desired settings
    // This part depends on the specific settings you want to use
    // You can refer to the OV7670 datasheet for register values
    
    // Example configuration:
    // writeRegister(REG_COM7, 0x80); // Reset to default values
    
    return true; // Return true if configuration succeeds
}

bool Camera::startCapture() {
    select();
    SPI.transfer(0x36); // COM7 register address
    SPI.transfer(0x00); // Set COM7 register to capture mode
    deselect();
    return true;
}

bool Camera::waitForVSYNC() {
    while (digitalRead(OV7670_VSYNC_PIN) == HIGH) {}
    while (digitalRead(OV7670_VSYNC_PIN) == LOW) {}
    return true;
}

void Camera::select() {
    digitalWrite(_csPin, LOW);
}

void Camera::deselect() {
    digitalWrite(_csPin, HIGH);
}

void Camera::writeRegister(uint8_t reg, uint8_t value) {
    select();
    SPI.transfer(reg | 0x80); // Set write mode for register
    SPI.transfer(value);
    deselect();
}

uint8_t Camera::readRegister(uint8_t reg) {
    select();
    SPI.transfer(reg); // Set read mode for register
    uint8_t value = SPI.transfer(0x00);
    deselect();
    return value;
}
