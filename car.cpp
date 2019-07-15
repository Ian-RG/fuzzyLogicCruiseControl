#include "car.h"
#include <iostream>
#include <cmath>
#include <vector>

Car::Car(int speedLimit)
{
    power = 0;
    speed = 0;
    accel = 0;
    //Control functions
    belowSetSpeedBig.setPoints(-10000, -8, -10000, -speedLimit);
    belowSetSpeedSmall.setPoints(-10, 0, -5);
    atSetSpeed.setPoints(-1, 1, 0);
    overSetSpeedSmall.setPoints(0, 10, 5);
    overSetSpeedBig.setPoints(8, 10000, speedLimit, 10000);

    deceleratingBig.setPoints(-1000, -5, -1000, -15);
    deceleratingSmall.setPoints(-6, 0, -3);
    stableChange.setPoints(-0.1, 0.1, 0);
    acceleratingSmall.setPoints(0, 6, 3);
    acceleratingBig.setPoints(5, 1000, 15, 1000);
}

double
Car::getSpeed(double roadAngle)
{
    double prevSpeed = speed;
    double effectivePower = power - roadAngle;

    speed += (effectivePower / 10);
    accel = (speed - prevSpeed) / 0.1;

    return speed;
}

void Car::setPower(int speedLimit)
{
    //Get memberships for each function
    double belowBig, belowSmall, at, overSmall, overBig, decelBig, decelSmall, stable, accelSmall, accelBig;
    belowBig = belowSetSpeedBig.getValue(speed - speedLimit);
    belowSmall = belowSetSpeedSmall.getValue(speed - speedLimit);
    at = atSetSpeed.getValue(speed - speedLimit);
    overSmall = overSetSpeedSmall.getValue(speed - speedLimit);
    overBig = overSetSpeedBig.getValue(speed - speedLimit);
    decelBig = deceleratingBig.getValue(accel);
    decelSmall = deceleratingSmall.getValue(accel);
    stable = stableChange.getValue(accel);
    accelSmall = acceleratingSmall.getValue(accel);
    accelBig = acceleratingBig.getValue(accel);

    std::cout << "Memberships:\n";
    std::cout << "belowBig: " << belowBig << std::endl;
    std::cout << "belowSmall: " << belowSmall << std::endl;
    std::cout << "at: " << at << std::endl;
    std::cout << "overSmall: " << overSmall << std::endl;
    std::cout << "overBig: " << overBig << std::endl;
    std::cout << "decelBig: " << decelBig << std::endl;
    std::cout << "decelSmall: " << decelSmall << std::endl;
    std::cout << "stable: " << stable << std::endl;
    std::cout << "accelSmall: " << accelSmall << std::endl;
    std::cout << "accelBig: " << accelBig << "\n\n";

    std::vector<std::pair<double, double>> memberships;
    auto addMember = [&memberships](double d1, double d2, double d3) { memberships.push_back(std::make_pair((d1 + d2) / 2, d3)); };

    //Average non-zero pairs and apply relevant rule to power output
    if (belowBig > 0)
    {
        if (accelBig > 0)
            addMember(belowBig, accelBig, MAX_SMALL_ACCEL_VAL);
        if (accelSmall > 0)
            addMember(belowBig, accelSmall, MAX_BIG_ACCEL_VAL);
        if (stable > 0)
            addMember(belowBig, stable, MAX_BIG_ACCEL_VAL);
        if (decelBig > 0)
            addMember(belowBig, decelBig, MAX_BIG_ACCEL_VAL);
        if (decelSmall > 0)
            addMember(belowBig, decelSmall, MAX_BIG_ACCEL_VAL);
    }
    if (belowSmall > 0)
    {
        if (accelBig > 0)
            addMember(belowSmall, accelBig, MAX_BIG_DECEL_VAL);
        if (accelSmall > 0)
            addMember(belowSmall, accelSmall, NO_CHANGE_VAL);
        if (stable > 0)
            addMember(belowSmall, stable, MAX_SMALL_ACCEL_VAL);
        if (decelBig > 0)
            addMember(belowSmall, decelBig, MAX_BIG_ACCEL_VAL);
        if (decelSmall > 0)
            addMember(belowSmall, decelSmall, MAX_SMALL_ACCEL_VAL);
    }
    if (at > 0)
    {
        if (accelBig > 0)
            addMember(at, accelBig, MAX_BIG_DECEL_VAL);
        if (accelSmall > 0)
            addMember(at, accelSmall, MAX_SMALL_DECEL_VAL);
        if (stable > 0)
            addMember(at, stable, NO_CHANGE_VAL);
        if (decelBig > 0)
            addMember(at, decelBig, MAX_BIG_ACCEL_VAL);
        if (decelSmall > 0)
            addMember(at, decelSmall, MAX_SMALL_ACCEL_VAL);
    }
    if (overSmall > 0)
    {
        if (accelBig > 0)
            addMember(overSmall, accelBig, MAX_BIG_DECEL_VAL);
        if (accelSmall > 0)
            addMember(overSmall, accelSmall, MAX_SMALL_DECEL_VAL);
        if (stable > 0)
            addMember(overSmall, stable, MAX_SMALL_ACCEL_VAL);
        if (decelBig > 0)
            addMember(overSmall, decelBig, MAX_SMALL_ACCEL_VAL);
        if (decelSmall > 0)
            addMember(overSmall, decelSmall, NO_CHANGE_VAL);
    }
    if (overBig > 0)
    {
        if (accelBig > 0)
            addMember(overBig, accelBig, MAX_BIG_DECEL_VAL);
        if (accelSmall > 0)
            addMember(overBig, accelSmall, MAX_BIG_DECEL_VAL);
        if (stable > 0)
            addMember(overBig, stable, MAX_BIG_DECEL_VAL);
        if (decelBig > 0)
            addMember(overBig, decelBig, MAX_SMALL_DECEL_VAL);
        if (decelSmall > 0)
            addMember(overBig, decelSmall, MAX_BIG_DECEL_VAL);
    }

    for (auto &p : memberships)
        p.first = 1 - (p.first / 2);

    double a = 0, b = 0;
    for (auto &p : memberships)
    {
        a += p.first * p.second;
        b += p.first;
    }

    if (b != 0)
        power += a / b;

    if (power > CAR_POWER_LIMIT)
        power = CAR_POWER_LIMIT;
}
