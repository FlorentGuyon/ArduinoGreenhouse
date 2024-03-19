/**
  * @file     CurrentSensor.h
  * @version  V1.0
  * @date     2017, May 31
  * @author   Florent Guyon | florent.guyon@protonmail.com
  * @brief    Definition of the CurrentSensor class
  *
  *  A0
  *  A1   INPUT     Current sensor data pin (ACS712)
  *  A2
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
  * ~09
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
#include "Regulator.h"          // Active a switch when a value is above or below a threshold
//#include "LightSensor.h"        // Read the illuminance
//#include "SoilHumiditySensor.h" // Read the amount of water in the soil

// ############################################################################ TYPES

// Pointer to a function
typedef void (*CallbackFunction)();

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
#define count_tasks 15

// ARDUINO RESET
#define arduino_reset_push_duration 5 * 1000UL // ms
#define arduino_reset_frequency 0.5 * 1000UL // ms

// TEMPERATURE SENSOR
#define temperature_sensor_pin 6
#define temperature_sensor_frequency 60 * 1000UL // ms

// CURRENT SENSOR
#define current_sensor_pin A1
#define current_sensor_frequency 20 * 1000UL // ms

// LCD SCREEN
#define lcd_screen_I2C_address 0x27
#define lcd_screen_count_columns 16
#define lcd_screen_count_lines 2
#define lcd_screen_count_texts 9
#define lcd_screen_seconds_per_text 2 // s
#define lcd_screen_frequency 1 * 1000UL // ms

// GAS SENSOR
#define gas_sensor_pin A3
#define gas_sensor_frequency 10 * 1000UL // ms

// HUMIDIFIER
#define humidifier_humidity_minimal_threshold 50 // %
#define humidifier_count_thresholds 1
#define humidifier_frequency 60 * 1000UL // ms

// LED STRIP
#define led_strip_illuminance_minimal_threshold 1200 // lux
#define led_strip_count_thresholds 1
#define led_strip_frequency 60 * 1000UL // ms

// REGISTERS
#define registers_SER_pin 2
#define registers_RCK_pin 3
#define registers_SCK_pin 4
#define count_registers 1
#define bit_per_register 8
#define registers_frequency 60 * 1000UL // ms

// SD CARD
#define sd_card_CS_pin 10
#define sd_card_data_file "data.csv"
#define sd_card_count_texts 16
#define sd_card_frequency 5 * 60 * 1000UL // ms

// PUSH BUTTON
#define push_button_pin 7
#define push_button_frequency 0.5 * 1000UL // ms

// BUZZER
#define buzzer_pin 8

// REAL TIME CLOCK
#define real_time_clock_I2C_address 0x68
#define real_time_clock_frequency 60 * 1000UL // ms

// WATER PUMP
#define water_pump_soil_humidity_minimal_threshold 50 // %
#define water_pump_count_thresholds 1
#define water_pump_frequency 60 * 1000UL // ms

// FANS
#define fans_temperature_maximal_threshold 20 // °C
#define fans_humidity_maximal_threshold 90 // %
#define fans_co2_level_maximal_threshold 400 // %
#define fans_count_thresholds 3
#define fans_frequency 60 * 1000UL // ms

// LIGHT SENSOR
#define light_sensor_frequency 60 * 1000UL // ms

// SOIL HUMIDITY SENSOR
#define soil_humidity_sensor_frequency 60 * 1000UL // ms

// ############################################################################ GLOBAL VARIABLES

// ARDUINO RESET
uint32_t arduino_reset_last_run = 0;

// TEMPERATURE SENSOR
uint32_t temperature_sensor_last_run = 0;

// HUMIDIFIER
uint32_t humidifier_last_run = 0;

// CURRENT SENSOR
uint32_t current_sensor_last_run = 0;

// GAS SENSOR
uint32_t gas_sensor_last_run = 0;

// LED STRIP
uint32_t led_strip_last_run = 0;

// CAMERA
uint32_t camera_last_run = 0;

// SD CARD
uint32_t sd_card_last_run = 0;

// LCD SCREEN
uint32_t lcd_screen_last_print = 0; // ms
uint8_t lcd_screen_text_index = 0;
uint32_t lcd_screen_last_run = 0;

// REGISTERS
uint32_t registers_last_run = 0;

// PUSH BUTTON
uint32_t push_button_last_run = 0;

// REAL TIME CLOCK
uint32_t real_time_clock_last_run = 0;

// WATER PUMP
uint32_t water_pump_last_run = 0;

// FANS
uint32_t fans_last_run = 0;

// LIGHT SENSOR
uint32_t light_sensor_last_run = 0;

// SOIL HUMIDITY SENSOR
uint32_t soil_humidity_sensor_last_run = 0;

// ############################################################################ DEVICES

Register registers(registers_SER_pin, registers_RCK_pin, registers_SCK_pin); // 5V
TemperatureSensor temperature_sensor(temperature_sensor_pin); // 3V
CurrentSensor current_sensor(current_sensor_pin); // 5V
LCDScreenWithI2C lcd_screen(lcd_screen_I2C_address, lcd_screen_count_columns, lcd_screen_count_lines); // 5V
GasSensor gas_sensor(gas_sensor_pin); // 5V
Pulsable buzzer(buzzer_pin); // 3V
SDCard sd_card(sd_card_CS_pin); // 5V
PushButton push_button(push_button_pin);
RealTimeClock real_time_clock; // 5V
Regulator humidifier; // 5V
Regulator led_strip; // 5V
Regulator water_pump; // 12V
Regulator fans;
//SoilHumiditySensor soil_humidity_sensor; // V
//LightSensor light_sensor; // V

// ############################################################################ DEVICES THRESHOLDS

// HUMIDIFIER
MinimalThreshold humidifier_humidity_threshold(&temperature_sensor._humidity, humidifier_humidity_minimal_threshold);

Threshold* humidifier_thresholds[humidifier_count_thresholds] = {
  &humidifier_humidity_threshold
};

// FANS
MaximalThreshold fans_co2_level_threshold(&gas_sensor._gas_concentration, fans_co2_level_maximal_threshold);
MaximalThreshold fans_temperature_threshold(&temperature_sensor._temperature, fans_temperature_maximal_threshold);
MaximalThreshold fans_humidity_threshold(&temperature_sensor._humidity, fans_humidity_maximal_threshold);

Threshold* fans_thresholds[fans_count_thresholds] = {
  &fans_temperature_threshold,
  &fans_humidity_threshold,
  &fans_co2_level_threshold
};

// WATER PUMP
//MinimalThreshold water_pump_soil_humidity_threshold(&soil_humidity_sensor._humidity, water_pump_soil_humidity_minimal_threshold);

//Threshold water_pump_thresholds[water_pump_count_thresholds] = {
//  &water_pump_soil_humidity_threshold
//};

// LED STRIP
//MinimalThreshold led_strip_illuminance_threshold(&light_sensor._illuminance, led_strip_illuminance_minimal_threshold);

//Threshold led_strip_thresholds[led_strip_count_thresholds] = {
//  &led_strip_illuminance_threshold
//};

// ############################################################################ DEVICES TO ACTIVATE

bool* switches[count_registers * bit_per_register] = {
  &led_strip._switch_value,
  &humidifier._switch_value,
  &water_pump._switch_value,
  &fans._switch_value
};

// ############################################################################ CALLBACK FUNCTIONS

void RealTimeClockRun() {
  Serial.print(F("Real time clock: "));
  Serial.println(real_time_clock.get_timedate());
}

void TemperatureSensorRun() {
  if (temperature_sensor.read_humidity_and_temperature()) {
    Serial.print(F("Temperature: "));
    Serial.print(temperature_sensor.get_temperature());
    Serial.println(F("°C"));
    Serial.print(F("Humidity: "));
    Serial.print(temperature_sensor.get_humidity());
    Serial.println(F("%"));
  }
}

void HumidifierRun() {
  // Turn the humidifier "ON" if the humidity is below the threshold
  humidifier.check_thresholds();    
  Serial.print(F("Humidifier: "));
  Serial.println(humidifier.get_switch_value() ? F("ON") : F("OFF"));
}

void GasSensorRun() {
  gas_sensor.set_humidity(temperature_sensor.get_humidity());
  gas_sensor.set_temperature(temperature_sensor.get_temperature());

  if (gas_sensor.read_data()) {
    Serial.print(F("CO2 level: "));
    Serial.print(gas_sensor.get_gas_concentration());  
    Serial.println(F("ppm"));
  } else {
    Serial.println(F("Unable to read data from the gas sensor."));
  }
}

void FansRun() {
  // Turn the fans "ON" if the CO2 level is above the threshold 
  fans.check_thresholds();    
  Serial.print(F("Fans: "));
  Serial.println(fans.get_switch_value() ? F("ON") : F("OFF"));
}

void LightSensorRun() {
  //
}

void LEDStripRun() {
  // Turn the LED strip "ON" if the illuminance is below the threshold
  led_strip.set_switch_value(false);    
  Serial.print(F("LED Strip: "));
  Serial.println(led_strip.get_switch_value() ? F("ON") : F("OFF"));
}

void SoilHumiditySensorRun() {
  //
}

void WaterPumpRun() {
  // Turn the water pump "ON" if the soil humidity is below the threshold
  water_pump.set_switch_value(false);    
  Serial.print(F("Water pump: "));
  Serial.println(led_strip.get_switch_value() ? F("ON") : F("OFF"));
}

void CurrentSensorRun() {
  if (current_sensor.read_current()) {
    Serial.print(F("Current: "));
    Serial.print(current_sensor.get_milliampere());
    Serial.println(F("mA"));
  }
}

void PushButtonRun() {
  if (push_button.read_push(arduino_reset_push_duration)) {
    Serial.print(F("Last push timestamp: "));
    Serial.println(push_button.get_last_push_timestamp());
    Serial.print(F("Last push duration: "));
    Serial.println(push_button.get_last_push_duration());
    Serial.print(F("Count pushes: "));
    Serial.println(push_button.get_count_pushes());
  }
}

void ArduinoResetRun() {  
  // If the last button pushing was long enough, reset the Arduino
  if (push_button.get_last_push_duration() >= arduino_reset_push_duration) {
    // Write it in the console
    Serial.print(F("Arduino reset..."));
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

void LCDScreenRun() {
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
        //
        String text;
        uint8_t text_index = 0;
        //
        if (lcd_screen_text_index == text_index++) {text = real_time_clock.get_timedate();}
        if (lcd_screen_text_index == text_index++) {text = "Air humidity " + String(temperature_sensor.get_humidity()) + "%";}
        if (lcd_screen_text_index == text_index++) {text = "Humidifier " + String(humidifier.get_switch_value() ? "ON" : "OFF");} 
        if (lcd_screen_text_index == text_index++) {text = "Temperature " +  String(temperature_sensor.get_temperature()) + "C";}
        if (lcd_screen_text_index == text_index++) {text = "CO2 " + String(gas_sensor.get_gas_concentration()) + "ppm";} 
        if (lcd_screen_text_index == text_index++) {text = "Fans " + String(fans.get_switch_value() ? "ON" : "OFF");}
        //if (lcd_screen_text_index == text_index++) {text = "Soil humidity " + String(soil_humidity_sensor.get_humidity()) + "%";}
        if (lcd_screen_text_index == text_index++) {text = "Water pump " + String(water_pump.get_switch_value() ? "ON" : "OFF");}
        //if (lcd_screen_text_index == text_index++) {text = "Illuminance " + String(light_sensor.get_illuminance()) + "lux";}
        if (lcd_screen_text_index == text_index++) {text = "LED strip " + String(led_strip.get_switch_value() ? "ON" : "OFF");}
        if (lcd_screen_text_index == text_index++) {text = "Current " + String(current_sensor.get_milliampere()) + "mA";} 
        //
        lcd_screen.write_text(text);
        //
        lcd_screen_last_print = millis();
        //
        lcd_screen_text_index += 1;
      }
      // If the prints are done
      else {
        lcd_screen.clear();
        lcd_screen.noBacklight();
      }
    }
  }
}

void RegistersRun() {
  // Turn "ON" and "OFF" the output devices
  registers.flush_bits();
  Serial.print(F("Bits: "));
  registers.print_bits();
}

void SDCardRun() {
  // Write in the console the texts written in the SD card
  Serial.print(F("SD Card: "));
  // Text written in the SD card
  String new_text;
  // Go through all the texts to write
  for (uint8_t current_index = 0; current_index <= sd_card_count_texts -1 ; ++current_index) {
    // Auto incremented variable for easier modifications
    uint8_t text_index = 0;
    // Choose the text to write in the SD card depending on the current index
    if (current_index == text_index++) {new_text = real_time_clock.get_timedate() + F(",");}                       // Timedate (yy-m-d h-m-s)
    if (current_index == text_index++) {new_text = String(temperature_sensor.get_temperature()) + F(",");}         // Temperature (°C)
    if (current_index == text_index++) {new_text = String(fans_temperature_maximal_threshold) + F(",");}           // Target temperature (°C)
    if (current_index == text_index++) {new_text = String(gas_sensor.get_gas_concentration()) + F(",");}           // CO2 level (ppm)
    if (current_index == text_index++) {new_text = String(fans_co2_level_maximal_threshold) + F(",");}             // Target CO2 level (ppm)
    if (current_index == text_index++) {new_text = String(fans.get_switch_value() * 100) + F(",");}                // Fans usage (%)
    if (current_index == text_index++) {new_text = String(temperature_sensor.get_humidity()) + F(",");}            // Air humidity (%)
    if (current_index == text_index++) {new_text = String(humidifier_humidity_minimal_threshold) + F(",");}        // Target air humidity (%)
    if (current_index == text_index++) {new_text = String(humidifier.get_switch_value() * 100) + F(",");}          // Humidifier usage (%)
    if (current_index == text_index++) {new_text = String(/*soil_humidity_sensor.get_humidity()*/) + F(",");}      // Soil humidity (%)
    if (current_index == text_index++) {new_text = String(water_pump_soil_humidity_minimal_threshold) + F(",");}   // Target soil humidity (%)
    if (current_index == text_index++) {new_text = String(water_pump.get_switch_value() * 100) + F(",");}          // Water pump usage (%)
    if (current_index == text_index++) {new_text = String(/*light_sensor.get_illuminance()*/) + F(",");}           // Illuminance (lux)
    if (current_index == text_index++) {new_text = String(led_strip_illuminance_minimal_threshold) + F(",");}      // Target illuminance (lux)
    if (current_index == text_index++) {new_text = String(led_strip.get_switch_value() * 100) + F(",");}           // LED strip usage (%)
    if (current_index == text_index++) {new_text = String(current_sensor.get_milliampere()) + F("\n");}            // Current consumption (mA)
    // Try to write the text in the SD card
    if (sd_card.write(sd_card_data_file, new_text)) {
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
      return;
    }
  }
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
  {RealTimeClockRun, real_time_clock_frequency, &real_time_clock_last_run},
  {TemperatureSensorRun, temperature_sensor_frequency, &temperature_sensor_last_run},
  {HumidifierRun, humidifier_frequency, &humidifier_last_run},
  {GasSensorRun, gas_sensor_frequency, &gas_sensor_last_run},
  {FansRun, fans_frequency, &fans_last_run},
  {LightSensorRun, light_sensor_frequency, &light_sensor_last_run},
  {LEDStripRun, led_strip_frequency, &led_strip_last_run},
  {SoilHumiditySensorRun, soil_humidity_sensor_frequency, &soil_humidity_sensor_last_run},
  {WaterPumpRun, water_pump_frequency, &water_pump_last_run},
  {CurrentSensorRun, current_sensor_frequency, &current_sensor_last_run},
  {PushButtonRun, push_button_frequency, &push_button_last_run},
  {LCDScreenRun, lcd_screen_frequency, &lcd_screen_last_run},
  {RegistersRun, registers_frequency, &registers_last_run},
  {SDCardRun, sd_card_frequency, &sd_card_last_run},
  {ArduinoResetRun, arduino_reset_frequency, &arduino_reset_last_run}
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
  temperature_sensor.initialize();
  Serial.println(F("Done."));

  // HUMIDIFIER
  Serial.print(F("Initializing humidifier... "));
  humidifier.set_thresholds(humidifier_thresholds);
  humidifier.set_count_thresholds(humidifier_count_thresholds);
  Serial.println(F("Done."));
  
  // LED STRIP
  Serial.print(F("Initializing LED strip... "));
  //led_strip.set_thresholds(led_strip_thresholds);
  led_strip.set_count_thresholds(led_strip_count_thresholds);
  Serial.println(F("Done."));
  
  // WATER PUMP
  Serial.print(F("Initializing water pump... "));
  //water_pump.set_thresholds(water_pump_thresholds);
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
  current_sensor.initialize();
  Serial.println(F("Done."));

  // REAL TIME CLOCK
  Serial.print(F("Initializing real time clock... "));
  real_time_clock.set_I2C_address(real_time_clock_I2C_address);
  real_time_clock.initialize();
  Serial.println(F("Done."));

  // END
  buzzer.pulse(50, 2, 50);
}

// ############################################################################ MAIN PROGRAM

void loop() {
  // For each task in the list
  for (uint8_t task_index = 0 ; task_index <= count_tasks -1 ; ++task_index) {
    // If the task has never been executed, or not for a long enough time
    if ((*tasks[task_index].last_run == 0) || ((millis() - *tasks[task_index].last_run) >= tasks[task_index].frequency)) {
      // Execute the callback function
      tasks[task_index].callback_function();
      // Reset the timer
      *tasks[task_index].last_run = millis();
    }
  }
  // Wait before evaluating all the tasks again
  delay(main_loop_frequency); // ms
}