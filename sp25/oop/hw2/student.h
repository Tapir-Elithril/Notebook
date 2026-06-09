# ifndef _STUDENT_H_
# define _STUDENT_H_
#include<string>
#include<map>

using namespace std;

class Student {
private:
    string name;
    map<string,int> score;
    float avaliable = 0;
    int no;
    float avg = 0;
public:
    static map<string,float> shared_average[2];
    // 0: average, 1: available
    static map<string,int> shared_min;
    static map<string,int> shared_max;
    static const string courses[9];
    Student();
    ~Student();
    void input(const string& line,int no);
    void output();
};

# endif