/**
  * @file     CurrentSensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the CurrentSensor class
  *
  *  A0
  *  A1   INPUT     Current sensor data pin (ACS712)
  *  A2   INPUT     Soil Humidity AO pin
  *  A3   INPUT     Gas sensor AO pin (MQ135)
  *  A4   OUTPUT    
  *  A5   OUTPUT    
  *
  * SCL   OUTPUT    LCD Screen I2C / Real time clock SCL pin
  * SDA   OUT/IN    LCD Screen I2C / Real time clock SDA pin
  *  13   OUTPUT    SD card SCK pin (forced)
  *  12   OUTPUT    SD card MISO pin (forced)
  * ~11   INPUT     SD card MOSI pin (forced)
  * ~10   OUTPUT    SD card CS pin
  * ~09   OUTPUT    Water pump relay pin
  *  08   OUTPUT    Buzzer pin
  *  07   INPUT     Push button pin
  * ~06   INPUT     Temperature sensor OUT pin
  * ~05
  *  04   OUTPUT    Registers SCK pin
  * ~03   OUTPUT    Registers RCK pin
  *  02   OUTPUT    Registers SER pin
  *  01
  *  00
  **/
  
// ############################################################################ LIBRARIES USEFULL TO RUN THE GREENHOUSE

#include <avr/wdt.h>            // Arduino reset
#include <stdint.h>             // Definition of the uint<x>_t types
#include "TemperatureSensor.h"  // Read the humidity and temperature of the air into the greenhouse
#include "CurrentSensor.h"      // Read the voltage and the ampere of current from the batteries - if there is no external power supply plugged in -
#include "LCDScreenWithI2C.h"   // Print text on a LCD screen
#include "GasSensor.h"          // Read the concentration of gas (NH3, NOx, alcohol, Benzene, smoke, CO2, ...) in the air 
#include "Pulsable.h"           // Allow to send pulses to a pin
#include "Register.h"           // Multiply the number of available pins
#include "SDCard.h"             // Write data in files
#include "LightSensor.h"        // Read the illuminance
#include "PushButton.h"         // Read the pushes of a button
#include "RealTimeClock.h"      // Save real time
#include "LightSensor.h"        // Read the illuminance
#include "SoilHumiditySensor.h" // Read the amount of water in the soil

// ############################################################################ TYPES

// Pointer to a function
typedef bool (*CallbackFunction)();

// ############################################################################ STRUCTURES

// Callback functions to call at a regular interval 
struct Task {
    CallbackFunction callback_function;
    uint32_t frequency; // ~7 weeks maximum
    uint32_t* last_run; // ~7 weeks maximum
};

// ############################################################################ CONSTANTS

// SERIAL COMMUNICATION
#define serial_communication_frequency 9600  // baud

// MAIN
#define main_loop_frequency 500 // ms
#define count_tasks 8

// ARDUINO RESET
#define arduino_reset_push_duration 5 * 1000UL // ms

// TEMPERATURE SENSOR
#define temperature_sensor_pin 6
#define temperature_sensor_frequency 10 * 60 * 1000UL // ms
#define temperature_sensor_minimum_acceptable_temperature 5 // °C
#define temperature_sensor_maximum_acceptable_temperature 30 // °C
#define temperature_sensor_temperature_tolerance 2 // °C
#define temperature_sensor_minimum_acceptable_humidity 10 // %
#define temperature_sensor_maximum_acceptable_humidity 100 // %
#define temperature_sensor_humidity_tolerance 10 // %

// CURRENT SENSOR
#define current_sensor_pin A1
#define current_sensor_frequency 60 * 1000UL // ms
#define current_sensor_minimum_acceptable_milliampere 25 // mA
#define current_sensor_maximum_acceptable_milliampere 3000 // mA
#define current_sensor_milliampere_tolerance 200 // mA

// LCD SCREEN
#define lcd_screen_I2C_address 0x27
#define lcd_screen_count_columns 16
#define lcd_screen_count_lines 2
#define lcd_screen_count_texts 10
#define lcd_screen_seconds_per_text 2 // s
#define lcd_screen_frequency 1 * 1000UL // ms

// GAS SENSOR
#define gas_sensor_pin A3
#define gas_sensor_frequency 10 * 60 * 1000UL // ms
#define gas_sensor_minimum_acceptable_gas_concentration 50 // ppm
#define gas_sensor_maximum_acceptable_gas_concentration 2000 // ppm
#define gas_sensor_gas_concentration_tolerance 100 // ppm

// HUMIDIFIER
#define humidifier_humidity_minimal_threshold 80 // %
#define humidifier_count_thresholds 1

// LED STRIP
#define led_strip_illuminance_minimal_threshold 500 // lux
#define led_strip_count_thresholds 1
#define led_stip_start_hour 7 // h
#define led_stip_stop_hour 20 // h

// REGISTERS
#define registers_SER_pin 2
#define registers_RCK_pin 3
#define registers_SCK_pin 4
#define count_registers 1
#define bit_per_register 8

// SD CARD
#define sd_card_CS_pin 10
#define sd_card_data_file "data.csv"
#define sd_card_count_texts 15
#define sd_card_frequency 60 * 60 * 1000UL // ms

// PUSH BUTTON
#define push_button_pin 7
#define push_button_frequency 0.5 * 1000UL // ms

// BUZZER
#define buzzer_pin 8

// REAL TIME CLOCK
#define real_time_clock_I2C_address 0x68

// WATER PUMP
#define water_pump_pin 9
#define water_pump_soil_humidity_minimal_threshold 70 // %
#define water_pump_count_thresholds 1
#define water_pump_pulse_duration 5000 // ms

// FANS
#define fans_temperature_maximal_threshold 24 // °C
#define fans_air_humidity_maximal_threshold 95 // %
#define fans_soil_humidity_maximal_threshold 75 // %
#define fans_co2_level_maximal_threshold 1000 // %
#define fans_count_thresholds 4

// LIGHT SENSOR
#define light_sensor_frequency 10 * 60 * 1000UL // ms
#define light_sensor_minimum_acceptable_illuminance 0 // lux
#define light_sensor_maximum_acceptable_illuminance 10000 // lux
#define light_sensor_illuminance_tolerance 100 // lux

// SOIL HUMIDITY SENSOR
#define soil_humidity_sensor_pin A2
#define soil_humidity_sensor_frequency 10 * 60 * 1000UL // ms
#define soil_humidity_sensor_minimum_acceptable_humidity 0 // %
#define soil_humidity_sensor_maximum_acceptable_humidity 100 // %
#define soil_humidity_sensor_humidity_tolerance 5 // %

// ############################################################################ GLOBAL VARIABLES

// TEMPERATURE SENSOR
uint32_t temperature_sensor_last_run = 0;

// CURRENT SENSOR
uint32_t current_sensor_last_run = 0;

// GAS SENSOR
uint32_t gas_sensor_last_run = 0;

// CAMERA
uint32_t camera_last_run = 0;

// SD CARD
uint32_t sd_card_last_run = 0;

// LCD SCREEN
uint32_t lcd_screen_last_print = 0; // ms
uint8_t lcd_screen_text_index = 0;
uint32_t lcd_screen_last_run = 0;

// PUSH BUTTON
uint32_t push_button_last_run = 0;

// LIGHT SENSOR
uint32_t light_sensor_last_run = 0;

// SOIL HUMIDITY SENSOR
uint32_t soil_humidity_sensor_last_run = 0;

// ############################################################################ DEVICES

CurrentSensor current_sensor(current_sensor_pin); // 5V
GasSensor gas_sensor(gas_sensor_pin); // 5V
LCDScreenWithI2C lcd_screen(lcd_screen_I2C_address, lcd_screen_count_columns, lcd_screen_count_lines); // 5V
LightSensor light_sensor; // 5V
Pulsable buzzer(buzzer_pin); // 3V
Pulsable water_pump; // 12V
PushButton push_button(push_button_pin);
RealTimeClock real_time_clock; // 5V
Register registers(registers_SER_pin, registers_RCK_pin, registers_SCK_pin); // 5V
SDCard sd_card(sd_card_CS_pin); // 5V
SoilHumiditySensor soil_humidity_sensor(soil_humidity_sensor_pin); // 5V
Switchable humidifier; // 5V
Switchable led_strip; // 12V
Switchable fans; // 12V
TemperatureSensor temperature_sensor(temperature_sensor_pin); // 3V

// ############################################################################ DEVICES THRESHOLDS
// The thresholds indicate the each limit below/above which the corresponding device is turned on
// - With a minimal threshold, the value as to be below to turn the device on
// - With a maximal threshold, the value as to be above to turn the device on
// The device is turned on if at least one of the threshold is reached
// The device is turned off if no threshold is reached

// HUMIDIFIER
MinimalThreshold humidifier_humidity_threshold(&temperature_sensor.get_humidity()->_value, sizeof(temperature_sensor.get_humidity()->_value), humidifier_humidity_minimal_threshold);

Threshold* humidifier_thresholds[humidifier_count_thresholds] = {
  &humidifier_humidity_threshold
};

// FANS
MaximalThreshold fans_co2_level_threshold(&gas_sensor.get_gas_concentration()->_value, sizeof(gas_sensor.get_gas_concentration()->_value), fans_co2_level_maximal_threshold);
MaximalThreshold fans_temperature_threshold(&temperature_sensor.get_temperature()->_value, sizeof(temperature_sensor.get_temperature()->_value), fans_temperature_maximal_threshold);
MaximalThreshold fans_air_humidity_threshold(&temperature_sensor.get_humidity()->_value, sizeof(temperature_sensor.get_humidity()->_value), fans_air_humidity_maximal_threshold);
MaximalThreshold fans_soil_humidity_threshold(&soil_humidity_sensor.get_humidity()->_value, sizeof(soil_humidity_sensor.get_humidity()->_value), fans_soil_humidity_maximal_threshold);

Threshold* fans_thresholds[fans_count_thresholds] = {
  &fans_co2_level_threshold,
  &fans_temperature_threshold,
  &fans_air_humidity_threshold,
  &fans_soil_humidity_threshold
};

// WATER PUMP
MinimalThreshold water_pump_soil_humidity_threshold(&soil_humidity_sensor.get_humidity()->_value, sizeof(soil_humidity_sensor.get_humidity()->_value), water_pump_soil_humidity_minimal_threshold);

Threshold* water_pump_thresholds[water_pump_count_thresholds] = {
  &water_pump_soil_humidity_threshold
};

// LED STRIP
MinimalThreshold led_strip_illuminance_threshold(&light_sensor.get_illuminance()->_value, sizeof(light_sensor.get_illuminance()->_value), led_strip_illuminance_minimal_threshold);

Threshold* led_strip_thresholds[led_strip_count_thresholds] = {
  &led_strip_illuminance_threshold
};

// ############################################################################ DEVICES TO ACTIVATE

// The switches hold the required state of the devices.
// If its value is "true", the corresponding device will 
// be turned on on the next call of the registers callback function
bool* switches[count_registers * bit_per_register] = {
  &led_strip._switch_value,
  &humidifier._switch_value,
  &fans._switch_value
};

// ############################################################################ CALLBACK FUNCTIONS

// The temperature sensor reads the temperature and humidity of the air
bool TemperatureSensorRun() {
  // Try to read the temperature and humidity of the air
  if (temperature_sensor.read_humidity_and_temperature()) {
    // Write the data in the console
    Serial.print(F("Temperature (°C): "));
    temperature_sensor.get_temperature()->print();
    Serial.print(F("Humidity (%): "));
    temperature_sensor.get_humidity()->print();
    // Call the humidifier callback function to check its thresholds
    HumidifierRun();
    // Call the fans callback function to check its thresholds
    FansRun();
    // Quit the function with a success code
    return true;
  } 
  // Quit the function with an error code
  return false;
}

// The humidifier increase the amount of moisture in the air
void HumidifierRun() {
  // Turn the humidifier on if one of its thresholds is reached
  humidifier.check_thresholds();    
  Serial.print(F("Humidifier: "));
  Serial.println(humidifier.get_switch_value() ? F("ON") : F("OFF"));
  // Call the registers callback function to check the switches
  RegistersRun();
}

// The gas sensor reads the level of CO2
bool GasSensorRun() {
  // Try to read the CO2 level
  if (gas_sensor.read_data()) {
    Serial.print(F("CO2 level (ppm): "));
    gas_sensor.get_gas_concentration()->print();
    // Call the fans callback function to check its thresholds
    FansRun();
    //
    return true;
  }
  // If it fails
  else {
    // Write it in the console
    Serial.println(F("Unable to read data from the gas sensor."));
    //
    return false;
  }
}

// The fans decrease the temperature, humidity and CO2 level
void FansRun() {
  // Turn the fans on if one of its thresholds is reached
  fans.check_thresholds();    
  Serial.print(F("Fans: "));
  Serial.println(fans.get_switch_value() ? F("ON") : F("OFF"));
  // Call the registers callback function to check the switches
  RegistersRun();
}

// The light sensor reads the illuminance
bool LightSensorRun() {  
  // In order to check if there is already enough light or if the LED stip is needed
  // The LED strip has to be turned off before reading the illuminance
  led_strip.set_switch_value(false);
  // Call the registers callback function to apply the changes
  RegistersRun();
  // Wait some time for the LED strip to be turned off
  delay(1000);
  // Then, try to read the illuminance
  if (light_sensor.read_illuminance()) {
    // Write the data in the console
    Serial.print(F("Illuminance (lux): "));
    light_sensor.get_illuminance()->print();
    // Call the LED strip callback function to check its thresholds
    LEDStripRun();
    // Quit the function with a success code
    return true;
  }
  // If it fails
  else {
    // Quit the function with an error code
    return false;
  }
  return true;
}

// The LED strip increases the illuminance
void LEDStripRun() {
  // In order to reproduce a natrural light cycle, the LED strip has to stay turned off outside daytime, even if its minimal illuminance threshold is reached.
  // If its daytime
  if ((real_time_clock.get_hour() >= led_stip_start_hour) and (real_time_clock.get_hour() <= led_stip_stop_hour)) {
    // Turn the LED strip on if one of its thresholds is reached
    led_strip.check_thresholds();   
    // Call the registers callback function to check the switches
    RegistersRun();
  } 
  // Write the LED strip state in the console
  Serial.print(F("LED Strip: "));
  Serial.println(led_strip.get_switch_value() ? F("ON") : F("OFF"));
}

// The soil humidity sensor reads the moisture level of soil
bool SoilHumiditySensorRun() {
  // Try to read the soil humidity
  if (soil_humidity_sensor.read_data()) {
    // Write the data in the console
    Serial.print(F("Soil humidity (%): "));
    soil_humidity_sensor.get_humidity()->print();
    // Call the water pump callback function to check its thresholds
    WaterPumpRun();
    // Call the fans callback function to check its thresholds
    FansRun();
    // Quit the function with a success code
    return true;
  } 
  // If it fails
  else {
    // Quit the function with an error code
    return false;
  }
}

// The water pump irrigates the soils
void WaterPumpRun() {
  // Turn the water pump on if one of its thresholds is reached
  water_pump.check_thresholds(water_pump_pulse_duration);
}

// The current sensor read the current drawn by the devices
bool CurrentSensorRun() {
  return true;
  // Try to read the current drawn
  if (current_sensor.read_current()) {
    Serial.print(F("Current (mA): "));
    current_sensor.get_milliampere()->print();
    //
    return true;
  }
  //
  return false;
}

// The push button turn on the LCD screen or reboot the board
bool PushButtonRun() {
  // Record the timestamp and duration of the push (if any), with a timeout 
  if (push_button.read_push(arduino_reset_push_duration)) {
    Serial.print(F("Last push timestamp: "));
    Serial.println(push_button.get_last_push_timestamp());
    Serial.print(F("Last push duration: "));
    Serial.println(push_button.get_last_push_duration());
    Serial.print(F("Count pushes: "));
    Serial.println(push_button.get_count_pushes());
    // Call the arduino reset callback function to check the last push
    ArduinoResetRun();
  }
  //
  return true;
}

// The arduino reset does a soft reboot of the board with a long press on the push button
void ArduinoResetRun() {  
  // If the last button pushing was long enough, reset the Arduino
  if (push_button.get_last_push_duration() >= arduino_reset_push_duration) {
    // Write it in the console
    Serial.println(F("Arduino reset..."));
    // Disable the watchdog timer to prevent automatic reset
    wdt_disable();
    // Delay to allow Serial to finish transmitting
    delay(1000);
    // Enable the watchdog timer with a short timeout
    wdt_enable(WDTO_15MS);
    // Wait undefinitly until the reset
    while(1);
  }
}

// The LCD screen prints data about all the devices
bool LCDScreenRun() {
  // If the push button has been pressed at least once
  if (push_button.get_count_pushes() > 0) {
    // If a new push happend
    if (push_button.get_last_push_timestamp() > lcd_screen_last_run) {
      // Restart the prints from the begining
      lcd_screen_text_index = 0;
    }
    // If the last print lasted long enough
    if ((millis() - lcd_screen_last_print) > (lcd_screen_seconds_per_text * 1000)) {
      // If the prints are not done
      if (lcd_screen_text_index <= lcd_screen_count_texts -1) {
        // Text to write on the LCD screen
        String lines[lcd_screen_count_lines];
        // Auto incremented variable for easy modifications
        uint8_t text_index = 0;
        // Text to write on the LCD screen depending on the current index
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Timedate:";
          lines[1] = real_time_clock.get_timedate();
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Air humidity:";
          lines[1] = String(temperature_sensor.get_humidity()->get_value()) + " %";
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Humidifier:";
          lines[1] = String(humidifier.get_switch_value() ? "ON" : "OFF");
        } 
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Temperature:";
          lines[1] = String(temperature_sensor.get_temperature()->get_value()) + " C";
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "CO2 level:";
          lines[1] = String(gas_sensor.get_gas_concentration()->get_value()) + " ppm";
        } 
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Soil humidity:";
          lines[1] = String(soil_humidity_sensor.get_humidity()->get_value()) + " %";
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Fans:";
          lines[1] = String(fans.get_switch_value() ? "ON" : "OFF");
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Illuminance:";
          lines[1] = String(light_sensor.get_illuminance()->get_value()) + " lux";
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "LED strip:";
          lines[1] = String(led_strip.get_switch_value() ? "ON" : "OFF");
        }
        if (lcd_screen_text_index == text_index++) {
          lines[0] = "Current:";
          lines[1] = String(current_sensor.get_milliampere()->get_value()) + " mA";
        } 
        // Write the text on the LCD screen
        lcd_screen.write_text(lines);
        // Save the timestamp to wait the right amount of time before printing the next text
        lcd_screen_last_print = millis();
        // Shift the next text to write by 1
        lcd_screen_text_index += 1;
      }
      // If all the texts have been printed
      else {
        // Clear the content of the LCD screen
        lcd_screen.clear();
        // Turn off the backlight of the LCD screen
        lcd_screen.noBacklight();
      }
    }
  }
  // Quit the function with a success code
  return true;
}

// The registers send a continuous HIGH signal to multiple devices 
void RegistersRun() {
  // Send the state of each bit to the registers
  registers.flush_bits();
  // Write in the console the state of each bit (switchable)
  Serial.print(F("Bits: "));
  registers.print_bits();
}

// The SD card stores data about all the devices
bool SDCardRun() {
  // If it is the first call of the SD card callback function
  if (sd_card_last_run == 0) {
    // Exit the function with a success code
    // So the data are saved in the SD card only from the second call, once the sensor values are stable averages
    return true;
  }
  // Write in the console the texts written in the SD card
  Serial.print(F("SD Card: "));
  // Text written in the SD card
  String new_text;
  // Go through all the texts to write
  for (uint8_t current_index = 0; current_index <= sd_card_count_texts -1 ; ++current_index) {
    // Auto incremented variable for easier modifications
    uint8_t text_index = 0;
    // Choose the text to write in the SD card depending on the current index
    if (current_index == text_index++) {new_text = real_time_clock.get_timedate() + F(",");}                              // Timedate (yy-m-d h-m-s)
    if (current_index == text_index++) {new_text = String(temperature_sensor.get_temperature()->get_average()) + F(",");} // Temperature (°C)
    if (current_index == text_index++) {new_text = String(fans_temperature_maximal_threshold) + F(",");}                  // Target temperature (°C)
    if (current_index == text_index++) {new_text = String(gas_sensor.get_gas_concentration()->get_average()) + F(",");}   // CO2 level (ppm)
    if (current_index == text_index++) {new_text = String(fans_co2_level_maximal_threshold) + F(",");}                    // Target CO2 level (ppm)
    if (current_index == text_index++) {new_text = String(fans.get_switch_value() * 100) + F(",");}                       // Fans usage (%)
    if (current_index == text_index++) {new_text = String(temperature_sensor.get_humidity()->get_average()) + F(",");}    // Air humidity (%)
    if (current_index == text_index++) {new_text = String(humidifier_humidity_minimal_threshold) + F(",");}               // Target air humidity (%)
    if (current_index == text_index++) {new_text = String(humidifier.get_switch_value() * 100) + F(",");}                 // Humidifier usage (%)
    if (current_index == text_index++) {new_text = String(soil_humidity_sensor.get_humidity()->get_average()) + F(",");}  // Soil humidity (%)
    if (current_index == text_index++) {new_text = String(water_pump_soil_humidity_minimal_threshold) + F(",");}          // Target soil humidity (%)
    if (current_index == text_index++) {new_text = String(light_sensor.get_illuminance()->get_average()) + F(",");}       // Illuminance (lux)
    if (current_index == text_index++) {new_text = String(led_strip_illuminance_minimal_threshold) + F(",");}             // Target illuminance (lux)
    if (current_index == text_index++) {new_text = String(led_strip.get_switch_value() * 100) + F(",");}                  // LED strip usage (%)
    if (current_index == text_index++) {new_text = String(current_sensor.get_milliampere()->get_average()) + F("\n");}    // Current consumption (mA)
    // Try to write the text in the SD card
    if (sd_card.write(sd_card_data_file, new_text)) {
      // Write in the console the texts written in the SD card
      Serial.print(new_text);
    } 
    // If it fails
    else {
      // Print a log in the console
      Serial.print(F("Unable to write \""));
      Serial.print(new_text);
      Serial.print(F("\" in the file \""));
      Serial.print(sd_card_data_file);
      Serial.println(F("\"."));
      // Quit the function
      return false;
    }
  }
  // Reset the average values of the sensors between two lines of data
  temperature_sensor.get_temperature()->reset_average();
  temperature_sensor.get_humidity()->reset_average();
  soil_humidity_sensor.get_humidity()->reset_average();
  light_sensor.get_illuminance()->reset_average();
  gas_sensor.get_gas_concentration()->reset_average();
  current_sensor.get_milliampere()->reset_average();
  //
  return true;
}

// ############################################################################ TASKS
//
// List of the callback functions to call within a regular interval of time
//
//  Task = [
//   {
//      Pointer to the callback function,
//      Frequency of the callback (ms),
//      Last call of the function (ms)
//    } 
//  ]
//
Task tasks[count_tasks] = {
  {TemperatureSensorRun, temperature_sensor_frequency, &temperature_sensor_last_run},
  {GasSensorRun, gas_sensor_frequency, &gas_sensor_last_run},
  {LightSensorRun, light_sensor_frequency, &light_sensor_last_run},
  {SoilHumiditySensorRun, soil_humidity_sensor_frequency, &soil_humidity_sensor_last_run},
  {CurrentSensorRun, current_sensor_frequency, &current_sensor_last_run},
  {PushButtonRun, push_button_frequency, &push_button_last_run},
  {LCDScreenRun, lcd_screen_frequency, &lcd_screen_last_run}, 
  {SDCardRun, sd_card_frequency, &sd_card_last_run}
};

// ############################################################################ INITIALISATION

void setup() {
  
  // BEGINING
  buzzer.pulse();

  // SERIAL COMMUNICATIONS
  Serial.begin(serial_communication_frequency);
  while (!Serial);
  Serial.println(F("Serial communication initiated."));

  // TEMPERATURE SENSOR
  Serial.print(F("Initializing temperature sensor... "));
  temperature_sensor.get_temperature()->set_minimum_acceptable(temperature_sensor_minimum_acceptable_temperature);
  temperature_sensor.get_temperature()->set_maximum_acceptable(temperature_sensor_maximum_acceptable_temperature);
  temperature_sensor.get_temperature()->set_tolerance(temperature_sensor_temperature_tolerance);
  temperature_sensor.initialize();
  Serial.println(F("Done."));

  // GAS SENSOR
  Serial.print(F("Initializing gas sensor... "));
  gas_sensor.get_gas_concentration()->set_minimum_acceptable(gas_sensor_minimum_acceptable_gas_concentration);
  gas_sensor.get_gas_concentration()->set_maximum_acceptable(gas_sensor_maximum_acceptable_gas_concentration);
  gas_sensor.get_gas_concentration()->set_tolerance(gas_sensor_gas_concentration_tolerance);
  gas_sensor.set_temperature_address(&temperature_sensor.get_temperature()->_value);
  gas_sensor.set_humidity_address(&temperature_sensor.get_humidity()->_value);
  Serial.println(F("Done."));

  // HUMIDIFIER
  Serial.print(F("Initializing humidifier... "));
  humidifier.set_thresholds(humidifier_thresholds);
  humidifier.set_count_thresholds(humidifier_count_thresholds);
  Serial.println(F("Done."));

  // LIGHT SENSOR
  Serial.print(F("Initializing light sensor... "));
  light_sensor.get_illuminance()->set_minimum_acceptable(light_sensor_minimum_acceptable_illuminance);
  light_sensor.get_illuminance()->set_maximum_acceptable(light_sensor_maximum_acceptable_illuminance);
  light_sensor.get_illuminance()->set_tolerance(light_sensor_illuminance_tolerance);
  light_sensor.initialize();
  Serial.println(F("Done."));
  
  // LED STRIP
  Serial.print(F("Initializing LED strip... "));
  led_strip.set_thresholds(led_strip_thresholds);
  led_strip.set_count_thresholds(led_strip_count_thresholds);
  Serial.println(F("Done."));
  
  // WATER PUMP
  Serial.print(F("Initializing water pump... "));
  water_pump.set_pulse_pin(water_pump_pin);
  water_pump.set_thresholds(water_pump_thresholds);
  water_pump.set_count_thresholds(water_pump_count_thresholds);
  Serial.println(F("Done."));
  
  // FANS
  Serial.print(F("Initializing fans... "));
  fans.set_thresholds(fans_thresholds);
  fans.set_count_thresholds(fans_count_thresholds);
  Serial.println(F("Done."));

  // REGISTERS
  Serial.print(F("Initializing registers... "));
  registers.set_switches(switches);
  registers.set_count_switches(count_registers * bit_per_register);
  registers.initialize();
  Serial.println(F("Done."));

  // SD CARD
  Serial.print(F("Initializing SD card... "));
  sd_card.initialize();
  Serial.println(F("Done."));

  // LCD SCREEN
  Serial.print(F("Initializing LCD screen... "));
  lcd_screen.initialize();
  Serial.println(F("Done."));

  // CURRENT SENSOR
  Serial.print(F("Initializing current sensor... "));
  current_sensor.get_milliampere()->set_minimum_acceptable(current_sensor_minimum_acceptable_milliampere);
  current_sensor.get_milliampere()->set_maximum_acceptable(current_sensor_maximum_acceptable_milliampere);
  current_sensor.get_milliampere()->set_tolerance(current_sensor_milliampere_tolerance);
  current_sensor.initialize();
  Serial.println(F("Done."));

  // REAL TIME CLOCK
  Serial.print(F("Initializing real time clock... "));
  real_time_clock.set_I2C_address(real_time_clock_I2C_address);
  real_time_clock.initialize();
  Serial.println(F("Done."));
  // If the real time clock has been reset
  if (!real_time_clock.is_ready()) {
    // Write it in the console
    Serial.println(F("The real time clock is not configured."));
  }

  // END
  buzzer.pulse(50, 2, 50);
}

// ############################################################################ MAIN PROGRAM

void loop() {
  // For each task in the list
  for (uint8_t task_index = 0 ; task_index <= count_tasks -1 ; ++task_index) {
    // If the task has never been executed, or not for a long enough time
    if ((*tasks[task_index].last_run == 0) || ((millis() - *tasks[task_index].last_run) >= tasks[task_index].frequency)) {
      // Try to execute the callback function
      if (tasks[task_index].callback_function()) {
        // If it succeed, reset the timer
        *tasks[task_index].last_run = millis();
      }
    }
  }
  // Wait before evaluating all the tasks again
  delay(main_loop_frequency); // ms
}