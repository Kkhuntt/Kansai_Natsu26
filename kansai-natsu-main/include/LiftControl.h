#ifndef LIFT_CONTROL_H
#define LIFT_CONTROL_H

#include <mcp_can.h>
#include <SPI.h>

// Controls main lift on CAN Bus 1, Motor ID 5
void driveMainLift(int upPressed, int downPressed, int liftPower);

// Controls back lift on CAN Bus 1, Motor ID 6
void driveBackLift(int upPressed, int downPressed, int liftPower);

// Sends lift currents to CAN Bus 1 (Motor IDs 5-8 frame)
void sendLiftFrame();

#endif