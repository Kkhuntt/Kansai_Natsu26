#include "Config.h"
#include "Display.h"
#include "CANBus.h"
#include "LiftControl.h"

int16_t targetCurrent1 = 0; // Motor 5: Main Lift
int16_t targetCurrent2 = 0; // Motor 6: Back Lift

void driveMainLift(int upPressed, int downPressed, int liftPower) {
    if (upPressed) {
        targetCurrent1 = liftPower;
    } else if (downPressed) {
        targetCurrent1 = -liftPower;
    } else {
        targetCurrent1 = 0;
    }
}

void driveBackLift(int upPressed, int downPressed, int liftPower) {
    if (upPressed) {
        targetCurrent2 = -liftPower;     // Triangle button -> Up
    } else if (downPressed) {
        targetCurrent2 = liftPower;    // Cross button -> Down
    } else {
        targetCurrent2 = 0;             // Idle
    }
}

void sendLiftFrame() {
    byte frame[8] = {0};

    // Motor 5 (Bytes 0 & 1) - Main Lift
    frame[0] = (targetCurrent1 >> 8) & 0xFF;
    frame[1] = targetCurrent1 & 0xFF;

    // Motor 6 (Bytes 2 & 3) - Back Lift
    frame[2] = (targetCurrent2 >> 8) & 0xFF;
    frame[3] = targetCurrent2 & 0xFF;

    // Motors 7 & 8 (Bytes 4-7) - free on this frame, wire up a 3rd/4th
    // lift-related motor here if you need one without touching Bus 2
    frame[4] = 0;
    frame[5] = 0;
    frame[6] = 0;
    frame[7] = 0;

    // Motor IDs 5-8 command frame, CAN Bus 1
    CAN_Bus1.sendMsgBuf(0x1FF, 0, 8, frame);

    if (targetCurrent1 != 0 || targetCurrent2 != 0) {
        showMessage("Lift Moving");
        Serial.printf("Main Lift: %d | Back Lift: %d\n", targetCurrent1, targetCurrent2);
    }
}