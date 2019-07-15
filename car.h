#include "fuzzyFunction.h"

#define CAR_POWER_LIMIT 15

struct Car
{
    double power, speed, accel;

    FuzzyTriangle belowSetSpeedSmall, atSetSpeed, overSetSpeedSmall, deceleratingSmall, stableChange, acceleratingSmall;
    FuzzyTrapezoid belowSetSpeedBig, overSetSpeedBig, deceleratingBig, acceleratingBig;

    Car(int speedLimit);
    double getSpeed(double roadAngle);
    void setPower(int speedLimit);
};