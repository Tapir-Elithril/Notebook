#include"fraction.h"

Fraction::Fraction()
{
    numerator = 1;
    denominator = 1;
}

Fraction::Fraction(int num, int denom)
{
    if(denom == 0)
        throw invalid_argument("Denominator cannot be zero.");
    numerator = num;
    denominator = denom;
}