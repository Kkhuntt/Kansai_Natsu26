#include "Config.h"
#include "CANBus.h"
#include "MotorFeedback.h"

MotorFeedback bus1Motors[8] = {};
MotorFeedback bus2Motors[8] = {};

static void readBus(MCP_CAN &bus, int intPin, MotorFeedback* motors) {
    if (digitalRead(intPin)) return; // HIGH = no message waiting on this bus

    unsigned long rxId;
    unsigned char len = 0;
    unsigned char rxBuf[8];
    bus.readMsgBuf(&rxId, &len, rxBuf);

    if (rxId < 0x201 || rxId > 0x208) return; // not a motor feedback frame
    int idx = rxId - 0x201;

    // Standard DJI feedback layout: [angle_hi, angle_lo, rpm_hi, rpm_lo, current_hi, current_lo, temp, reserved]
    motors[idx].angle   = (rxBuf[0] << 8) | rxBuf[1];
    motors[idx].rpm     = (rxBuf[2] << 8) | rxBuf[3];
    motors[idx].current = (rxBuf[4] << 8) | rxBuf[5];
}

void updateMotorFeedback() {
    readBus(CAN_Bus1, canInt, bus1Motors);
    readBus(CAN_Bus2, canInt2, bus2Motors);
}