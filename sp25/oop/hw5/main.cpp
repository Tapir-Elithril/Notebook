#include "fraction.h"

int main()
{
    cout << "===== TEST1:Constructor =====" << endl;
    try {
        Fraction f1;
        cout << "Default Ctor:f1 = " << f1 << endl;    
        Fraction f2(2,3);
        cout << "Int parameter Ctor f2 = " << f2 << endl;
        Fraction f3 = f2;
        cout << "Copy Ctor: f3 = " << f3 << endl;
        //cout << "Note:This may not test the existence of copy ctor since the compiler may automatically give a default one." << endl;
        cout << "...Try to construct a fraction: 1/0" << endl;
        Fraction f4(1,0);
    } catch (const invalid_argument& e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "===== TEST2:Arithmetical operators =====" << endl;
    try {
        Fraction f1;
        Fraction f2(2,3);
        Fraction f3 = f2;
        Fraction f_plus = f2 + f3;
        cout << f2 << " + " << f3 << " = " << f_plus << endl;
        Fraction f_minus = f2 - Fraction(8,7);
        cout << f2 << " - " << Fraction(8,7) << " = " << f_minus << endl;
        Fraction f_mul = Fraction(7,12) * f_plus;
        cout << Fraction(7,12) << " * " << f_plus << " = " << f_mul << endl;
        Fraction f_div = f_mul / f_minus;
        cout << f_mul << " / " << f_minus << " = " << f_div << endl;
        cout << "...Try to divide 0" << endl;
        cout << f_div << " / " << Fraction(0,1) << endl;
        Fraction f_div0 = f_div / Fraction(0,1);
    } catch (const invalid_argument& e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "===== TEST3:Relational operators =====" << endl;
    try {
        Fraction f1;
        Fraction f2(2,3);
        Fraction f3(6,9);
        Fraction f4(7,7);
        cout << f1 << " < " << f2 << " : " << (f1 < f2 ? "True" : "False") << endl;
        cout << f1 << " < " << f4 << " : " << (f1 < f4 ? "True" : "False") << endl;
        cout << f1 << " <= " << f2 << " : " << (f1 <= f2 ? "True" : "False") << endl;
        cout << f3 << " <= " << f2 << " : " << (f3 <= f2 ? "True" : "False") << endl;
        cout << f1 << " == " << f2 << " : " << (f1 == f2 ? "True" : "False") << endl;
        cout << f3 << " == " << f2 << " : " << (f3 == f2 ? "True" : "False") << endl;
        cout << f1 << " != " << f4 << " : " << (f1 != f4 ? "True" : "False") << endl;
        cout << f2 << " != " << f4 << " : " << (f2 != f4 ? "True" : "False") << endl;
        cout << f1 << " >= " << f2 << " : " << (f1 >= f2 ? "True" : "False") << endl;
        cout << f1 << " >= " << f4 << " : " << (f1 >= f4 ? "True" : "False") << endl;
        cout << f1 << " > " << f2 << " : " << (f1 > f2 ? "True" : "False") << endl;
        cout << f3 << " > " << f2 << " : " << (f3 > f2 ? "True" : "False") << endl;
    } catch (const invalid_argument& e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "===== TEST4:Typecast =====" << endl;
    Fraction f;

    cout << "=== TEST4.1:Normal ===" << endl;
    try {
        cout << "Simulate input: 3/4" << endl;
        stringstream input("3/4"); 
        input >> f;
        cout << "Fraction: " << f << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "=== TEST4.2:Missing slash ===" << endl;
    try {
        cout << "Simulate input: 3 4" << endl;
        stringstream input("3 4"); 
        input >> f;
        cout << "Fraction: " << f << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "=== TEST4.3:0 denominator ===" << endl;
    try {
        cout << "Simulate input: 3/0" << endl;
        stringstream input("3/0"); 
        input >> f;
        cout << "Fraction: " << f << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "=== TEST4.4:Other invalid input(letters) ===" << endl;
    try {
        cout << "Simulate input: abc/def" << endl;
        stringstream input("abc/def"); 
        input >> f;
        cout << "Fraction: " << f << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "===== TEST5:Conversion from finite decimal string =====" << endl;
    cout << "=== TEST5.1:Normal ===" << endl;
    try {
        Fraction f,f1,f2,f3,f4;
        string s1 = "0",s2 = "1",s3 = "0.12",s4 = "12.34";
        f1 = f.conversion(s1);
        cout << "decimal_num:" << s1 << " fraction:" << f1 << endl;
        f2 = f.conversion(s2);
        cout << "decimal_num:" << s2 << " fraction:" << f2 << endl;
        f3 = f.conversion(s3);
        cout << "decimal_num:" << s3 << " fraction:" << f3 << endl;
        f4 = f.conversion(s4);
        cout << "decimal_num:" << s4 << " fraction:" << f4 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }
    cout << "=== TEST5.2:Abnormal input that can pass ===" << endl;
    try {
        Fraction f,f1,f2,f3,f4,f5;
        string s1 = ".123",s2 = "00.121",s3 = "012.34",s4 = "78.900",s5 = "013.00";
        f1 = f.conversion(s1);
        cout << "decimal_num:" << s1 << " fraction:" << f1 << endl;
        f2 = f.conversion(s2);
        cout << "decimal_num:" << s2 << " fraction:" << f2 << endl;
        f3 = f.conversion(s3);
        cout << "decimal_num:" << s3 << " fraction:" << f3 << endl;
        f4 = f.conversion(s4);
        cout << "decimal_num:" << s4 << " fraction:" << f4 << endl;
        f5 = f.conversion(s5);
        cout << "decimal_num:" << s5 << " fraction:" << f5 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }
    cout << "=== TEST5.3:Invalid input ===" << endl;
    try {
        Fraction f,f0;
        string s = "abc";
        cout << "decimal_num:" << s << endl;
        f0 = f.conversion(s);
        cout << "decimal_num:" << s << " fraction:" << f0 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }
    try {
        Fraction f,f0;
        string s = "123.p";
        cout << "decimal_num:" << s << endl;
        f0 = f.conversion(s);
        cout << "decimal_num:" << s << " fraction:" << f0 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }
    try {
        Fraction f,f0;
        string s = "2.3.4";
        cout << "decimal_num:" << s << endl;
        f0 = f.conversion(s);
        cout << "decimal_num:" << s << " fraction:" << f0 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }
    try {
        Fraction f,f0;
        string s = ".";
        cout << "decimal_num:" << s << endl;
        f0 = f.conversion(s);
        cout << "decimal_num:" << s << " fraction:" << f0 << endl;
    } catch (const exception &e) {
        cout << "Catch Exception: " << e.what() << endl;
    }

    cout << "===== Test succeed =====" << endl;
    return 0;
}