#include <cmath>

class __BigInt__
{
public:
    static long long asIntN(long long value, int bits)
    {
        if (bits < 1)
        {
            return 0;
        }

        long long minVal = -static_cast<long long>(std::pow(2, bits - 1));
        long long maxVal = static_cast<long long>(std::pow(2, bits - 1)) - 1;

        if (value < minVal)
        {
            return minVal;
        }
        else if (value > maxVal)
        {
            return maxVal;
        }
        else
        {
            return static_cast<long long>(value);
        }
    }

    static unsigned long long asUintN(unsigned long long value, int bits)
    {
        if (bits < 1)
        {
            return 0;
        }

        unsigned long long maxVal = static_cast<unsigned long long>(std::pow(2, bits)) - 1;

        if (value > maxVal)
        {
            return maxVal;
        }
        else if (value < 0)
        {
            return 0;
        }
        else
        {
            return static_cast<unsigned long long>(value);
        }
    }
};