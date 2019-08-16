#define MAX_BIG_ACCEL_VAL 5
#define MAX_SMALL_ACCEL_VAL 2.5
#define MAX_BIG_DECEL_VAL -5
#define MAX_SMALL_DECEL_VAL -2.5
#define NO_CHANGE_VAL 0

struct FuzzyTriangle
{
    double left, right, middle;

    FuzzyTriangle();
    void setPoints(double l, double r, double m);
    double getValue(double v);
};

struct FuzzyTrapezoid
{
    double left, right, lMiddle, rMiddle;
    FuzzyTrapezoid();
    void setPoints(double l, double r, double lMid, double rMid);
    double getValue(double v);
};