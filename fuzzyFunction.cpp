#include "fuzzyFunction.h"

FuzzyTriangle::FuzzyTriangle()
{
    left = 0;
    right = 0;
    middle = 0;
}

void FuzzyTriangle::setPoints(double l, double r, double m)
{
    left = l;
    right = r;
    middle = m;
}

double FuzzyTriangle::getValue(double v)
{
    if (v < left)
        return 0;
    else if (v < middle)
        return (v - left) / (middle - left);
    else if (v == middle)
        return 1;
    else if (v < right)
        return (right - v) / (right - middle);
    else
        return 0;
}

FuzzyTrapezoid::FuzzyTrapezoid()
{
    left = 0;
    right = 0;
    lMiddle = 0;
    rMiddle = 0;
}

void FuzzyTrapezoid::setPoints(double l, double r, double lMid, double rMid)
{
    left = l;
    right = r;
    lMiddle = lMid;
    rMiddle = rMid;
}

double FuzzyTrapezoid::getValue(double v)
{
    if (v < left)
        return 0;
    else if (v < lMiddle)
        return (v - left) / (lMiddle - left);
    else if (v >= lMiddle && v <= rMiddle)
        return 1;
    else if (v < right)
        return (right - v) / (right - rMiddle);
    else
        return 0;
}
