#include"fraction.h"
#include<algorithm>
#include<cmath>

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

Fraction::Fraction(const Fraction &f)
{
    this->numerator = f.getNumerator();
    this->denominator = f.getDenominator();
}

Fraction::~Fraction(){}

void Fraction::setNumerator(int num)
{
    this->numerator = num;
}

void Fraction::setDenominator(int denom)
{
    this->denominator = denom;
}

int Fraction::getNumerator() const
{
    return this->numerator;
}

int Fraction::getDenominator() const
{
    return this->denominator;
}

void Fraction::prt() const
{
    cout << numerator << "/" << denominator;
}

const Fraction operator+(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    int num_res = num1 * denom2 + num2 * denom1;
    int denom_res = denom1 * denom2;
    return Fraction(num_res,denom_res);
}

const Fraction operator-(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    int num_res = num1 * denom2 - num2 * denom1;
    int denom_res = denom1 * denom2;
    return Fraction(num_res,denom_res);
}

const Fraction operator*(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    int num_res = num1 * num2;
    int denom_res = denom1 * denom2;
    return Fraction(num_res,denom_res);
}

const Fraction operator/(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    if(num1 == 0 || num2 == 0)
        throw invalid_argument("cannot divide 0!");
    int num_res = num1 * denom2;
    int denom_res = denom1 * num2;
    return Fraction(num_res,denom_res);
}

bool operator<(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    return num1 * denom2 < num2 * denom1;
}

bool operator<=(const Fraction &f1,const Fraction &f2)
{
    return !(f2 < f1);
}

bool operator==(const Fraction &f1,const Fraction &f2)
{
    int num1 = f1.getNumerator();
    int num2 = f2.getNumerator();
    int denom1 = f1.getDenominator();
    int denom2 = f2.getDenominator();
    return num1 * denom2 == num2 * denom1;
}

bool operator!=(const Fraction &f1,const Fraction &f2)
{
    return !(f1 == f2);
}

bool operator>=(const Fraction &f1,const Fraction &f2)
{
    return !(f1 < f2);
}

bool operator>(const Fraction &f1,const Fraction &f2)
{
    return f2 < f1;
}

Fraction::operator double() const
{
    return numerator / (double)denominator;
}

Fraction::operator string() const
{
    return to_string(numerator) + "/" + to_string(denominator);
}

ostream &operator<<(ostream &os, const Fraction &f)
{
    os << f.numerator << "/" << f.denominator;
    return os;
}

istream &operator>>(istream &is, Fraction &f)
{
    string input;
    //cout << "Enter fraction in the form 'numerator/denominator': ";
    is >> input;
    
    stringstream ss(input);
    char slash;// '/'

    if(ss >> f.numerator >> slash >> f.denominator)
    {
        if(slash != '/')
            throw invalid_argument("Invalid fraction format");
        else if(f.denominator == 0)
            throw invalid_argument("Denomiator cannot be zero!");
    }
    else {
        throw invalid_argument("Invalid fraction format");
    }
    return is;
}

Fraction Fraction::conversion(string decimal_num) const
{
    char dictionary[11] = {'0','1','2','3','4','5','6','7','8','9','.'};

    //if not number,throw exception
    for(int i = 0; i < decimal_num.length(); ++i)
    {
        if(find(begin(dictionary), end(dictionary), decimal_num[i]) == end(dictionary))
            throw invalid_argument("Invalid decimal_num");
    }
    //if more than one '.',throw exception
    int dot_count = count(decimal_num.begin(),decimal_num.end(),'.');
    if(dot_count > 1 || (dot_count == 1 && decimal_num.length() == 1))
        throw invalid_argument("Invalid decimal_num");
    //split by '.'
    int dot_index = decimal_num.find('.');
    if(dot_index == '0')
    {
        decimal_num.insert(0,"0");
    }

    //if unappropriate '0',erase it,e.g 00.121,012.34,78.900,013.00
    int erase_count = 0;
    for(int i = 0; i < decimal_num.length(); ++i)
    {
        if(decimal_num[i] == '0' && decimal_num.length() != i + 1 && decimal_num[i+1] != '.')
            erase_count ++;
        else 
            break;
    }
    decimal_num.erase(0,erase_count);

    int back_erase_count = 0;
    if(dot_count == 1)
    {
        dot_index = decimal_num.find('.');
        for(int i = decimal_num.length() - 1; i > dot_index ; --i)
        {
            if(decimal_num[i] == '0')
                back_erase_count ++;
            else 
                break;
        }
    }
    decimal_num.erase(decimal_num.length() - back_erase_count,back_erase_count);
    if(decimal_num[decimal_num.length() - 1] == '.')
        decimal_num.erase(decimal_num.length() - 1,1);

    //123 -> 123/1,3.141 -> 3141/1000,0.0012 -> 12/10000,12.34 = 1234/100
    dot_index = decimal_num.find('.');
    
    if(dot_index == string::npos)
        return Fraction(stoi(decimal_num),1);
    else
    {
        int power = decimal_num.length() - dot_index - 1;
        int res = int(pow(10,power));
        //erase dot
        decimal_num.erase(dot_index,1);
        return Fraction(stoi(decimal_num),res);
    }

}