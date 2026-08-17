#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <mcp_can.h>
#include <SPI.h>

// Drives mecanum chassis on CAN Bus 1, Motor IDs 1-4 (frame 0x200)
void driveMecanum(int forward, int sideways, int turn, int maxCurrent);

#endif