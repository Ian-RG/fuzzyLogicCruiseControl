#include <ctime>
#include <iostream>
#include <iomanip>
#include "car.h"

#define SIM_ITER_COUNT 100

int main()
{
    auto stamp = std::clock();
    int count = 0;
    const int speedLimit = 50;
    Car car(speedLimit);

    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    while (count < SIM_ITER_COUNT)
    {
        if (std::clock() >= stamp + 100)
        {
            std::cout << std::string(100, '\n');
            std::cout << "Effective Road Angle: " << 0 << "\tSpeed Limit: " << speedLimit << std::endl;
            car.setPower(speedLimit);
            std::cout << "Speed: " << car.getSpeed(0) << std::endl;
            std::cout << "Acceleration: " << car.accel << std::endl;
            count++;
            stamp = std::clock();
        }
    }

    count = 0;
    while (count < SIM_ITER_COUNT)
    {
        if (std::clock() >= stamp + 100)
        {
            std::cout << std::string(100, '\n');
            std::cout << "Effective Road Angle: " << 5 << "\tSpeed Limit: " << speedLimit << std::endl;
            car.setPower(speedLimit);
            std::cout << "Speed: " << car.getSpeed(5) << std::endl;
            std::cout << "Acceleration: " << car.accel << std::endl;
            count++;
            stamp = std::clock();
        }
    }

    count = 0;
    while (count < SIM_ITER_COUNT)
    {
        if (std::clock() >= stamp + 100)
        {
            std::cout << std::string(100, '\n');
            std::cout << "Effective Road Angle: " << 10 << "\tSpeed Limit: " << speedLimit << std::endl;
            car.setPower(speedLimit);
            std::cout << "Speed: " << car.getSpeed(10) << std::endl;
            std::cout << "Acceleration: " << car.accel << std::endl;
            count++;
            stamp = std::clock();
        }
    }
}