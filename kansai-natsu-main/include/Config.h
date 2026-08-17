#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- CAN Bus 1 (Drivebase: Motor IDs 1-4, Lift: Motor IDs 5-6) ---
#define canInt 4            // CAN BUS 1 INTERRUPT PIN
#define canCs 5              // CAN BUS 1 CHIP SELECT

// --- CAN Bus 2 (Mechanisms: claw / shooter / step-climb, Motor IDs 1-8) ---
#define canInt2 26          // CAN BUS 2 INTERRUPT PIN
#define canCs2 27            // CAN BUS 2 CHIP SELECT
// NOTE: both MCP2515 modules share the same SPI bus (MOSI/MISO/SCK) on
// default VSPI pins — only CS and INT need to be unique per module.

#define buzzerPin 15        //BUZZER PIN FOR PURPLE PCB
#define MAX_SPEED 8000      //maximum is 16000, 
#define LIFT_POWER 7000     // Lift Speed

const int SDA_PIN = 32;
const int SCL_PIN = 33;

const float kP = 0.5;  
const float kI = 0.01; 
const float kD = 0.05;  


#endif
