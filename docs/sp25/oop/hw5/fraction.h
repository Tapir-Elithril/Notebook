#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Fraction {
private:
    int numerator;//分子
    int denominator;//分母
public:

    Fraction();
    Fraction(int num, int denom);
    Fraction(const Fraction &f);

    ~Fraction();

    void setNumerator(int num);
    void setDenominator(int denom);
    int getNumerator() const;
    int getDenominator() const;

    void prt() const;

    friend const Fraction operator+(const Fraction &f1,const Fraction &f2);
    friend const Fraction operator-(const Fraction &f1,const Fraction &f2);
    friend const Fraction operator*(const Fraction &f1,const Fraction &f2);
    friend const Fraction operator/(const Fraction &f1,const Fraction &f2);

    friend bool operator<(const Fraction &f1,const Fraction &f2);
    friend bool operator<=(const Fraction &f1,const Fraction &f2);
    friend bool operator==(const Fraction &f1,const Fraction &f2);
    friend bool operator!=(const Fraction &f1,const Fraction &f2);
    friend bool operator>=(const Fraction &f1,const Fraction &f2);
    friend bool operator>(const Fraction &f1,const Fraction &f2);

    operator double() const;
    operator string() const;

    friend ostream &operator<<(ostream &os, const Fraction &f);
    friend istream &operator>>(istream &is, Fraction &f);

    Fraction conversion(string decimal_num) const;
};

#endif