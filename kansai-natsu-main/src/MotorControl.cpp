#include "Config.h"
#include "Display.h"
#include "CANBus.h"
#include "MotorControl.h"

void driveMecanum(int forward, int sideways, int turn, int maxCurrent) {

    // Kinematic equations for Mecanum (M1: FL, M2: FR, M3: BL, M4: BR)
    float m1 =  forward + sideways + turn; // M1: Front Left
    float m2 = -forward + sideways + turn; // M2: Front Right
    float m3 =  forward - sideways + turn; // M3: Back Left
    float m4 = -forward - sideways + turn; // M4: Back Right

    // Map outputs to target motor currents
    int16_t c1 = constrain(map(m1, -256, 256, -maxCurrent, maxCurrent), -maxCurrent, maxCurrent);
    int16_t c2 = constrain(map(m2, -256, 256, -maxCurrent, maxCurrent), -maxCurrent, maxCurrent);
    int16_t c3 = constrain(map(m3, -256, 256, -maxCurrent, maxCurrent), -maxCurrent, maxCurrent);
    int16_t c4 = constrain(map(m4, -256, 256, -maxCurrent, maxCurrent), -maxCurrent, maxCurrent);

    // Build the 8-byte CAN payload for Motor IDs 1-4
    byte frame[8];
    frame[0] = (c1 >> 8) & 0xFF;
    frame[1] = c1 & 0xFF;
    frame[2] = (c2 >> 8) & 0xFF;
    frame[3] = c2 & 0xFF;
    frame[4] = (c3 >> 8) & 0xFF;
    frame[5] = c3 & 0xFF;
    frame[6] = (c4 >> 8) & 0xFF;
    frame[7] = c4 & 0xFF;

    if (abs(c1) > 0 || abs(c2) > 0 || abs(c3) > 0 || abs(c4) > 0) {
        showMessage("Mecanum Moving");
        Serial.printf("Drive Currents - M1: %d | M2: %d | M3: %d | M4: %d\n", c1, c2, c3, c4);
    }

    // Motor IDs 1-4 command frame, CAN Bus 1
    CAN_Bus1.sendMsgBuf(0x200, 0, 8, frame);
}