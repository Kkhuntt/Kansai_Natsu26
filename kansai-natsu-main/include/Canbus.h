#include "Config.h"
#include "Display.h"
#include "CANBus.h"

MCP_CAN CAN_Bus1(canCs);
MCP_CAN CAN_Bus2(canCs2);

static bool initSingleBus(MCP_CAN &bus, const char* label) {
    if (bus.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) == CAN_OK) {
        bus.setMode(MCP_NORMAL);
        Serial.printf("%s Initialized Successfully!\n", label);
        return true;
    } else {
        Serial.printf("Error Initializing %s...\n", label);
        return false;
    }
}

bool initCANBuses() {
    bool ok1 = initSingleBus(CAN_Bus1, "CAN Bus 1 (Drive/Lift)");
    bool ok2 = initSingleBus(CAN_Bus2, "CAN Bus 2 (Mechanisms)");

    if (!ok1 || !ok2) {
        showMessage("CAN Bus Init Failed");
        delay(100);
    }
    return ok1 && ok2;
}