#ifndef MOTOR_FEEDBACK_H
#define MOTOR_FEEDBACK_H

#include <mcp_can.h>

// One DJI feedback frame gives you angle, RPM, and current together —
// read it once per motor rather than parsing it twice in two functions.
struct MotorFeedback
{
    short angle;
    short rpm;
    short current;
};

// Index 0 = Motor ID 1 ... Index 7 = Motor ID 8, per bus.
extern MotorFeedback bus1Motors[8]; // Bus 1: Drive (1-4) + Lift (5-6)
extern MotorFeedback bus2Motors[8]; // Bus 2: Claw / Shooter / Step-climb

// Call every loop iteration. Services one pending message per bus, if any.
void updateMotorFeedback();

#endif