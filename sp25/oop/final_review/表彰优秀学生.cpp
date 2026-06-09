#include<iostream>
#include <string>
using namespace std;

/* 请在这里填写答案 */
class Student{
public:
    Student(string nnum,string nname):num(nnum),name(nname){};
    virtual ~Student() = default;
    virtual void display() const = 0;
protected:
    string num;
    string name;
    static double award_score;
};
double Student::award_score = 0;

class GroupA : public Student{
public:
    GroupA(string nnum,string nname,int ss1,int ss2)
        :Student(nnum,nname),s1(ss1),s2(ss2)
    {
        average = (s1 + s2)/2;
        award_score = average > award_score ? average : award_score;
    }
    ~GroupA() = default;
    void display() const override{
        if(average >= award_score)
            cout << num << " " << name << endl;
    }
private:
    int s1;
    int s2;
    double average;
};

class GroupB : public Student{
public:
    GroupB(string nnum,string nname,int ss1,int ss2,char ggs)
        :Student(nnum,nname),s1(ss1),s2(ss2),gs(ggs)
    {
        average = (s1 + s2)/2;
        award_score = average > award_score ? average : award_score;
    }
    ~GroupB() = default;
    void display() const override{
        if((average >= award_score)||((average >= award_score * 0.7)&&(gs =='A')))
            cout << num << " " << name << endl;
    }
private:
    int s1;
    int s2;
    double average;
    char gs;
};

class GroupC : public Student{
public:
    GroupC(string nnum,string nname,int ss1,int ss2,int ss3,int ss4,int ss5)
        :Student(nnum,nname),s1(ss1),s2(ss2),s3(ss3),s4(ss4),s5(ss5)
    {
        average = (s1 + s2 + s3 + s4 + s5)/5;
        //award_score = average > award_score ? average : award_score;
    }
    ~GroupC() = default;
    void display() const override{
        if(average >= award_score * 0.9)
            cout << num << " " << name << endl;
    }
private:
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    double average;
};

int main()
{
    const int Size=50;
    string num, name;
    int i,ty,s1,s2,s3,s4,s5;
    char gs;
    Student *pS[Size];
    int count=0;
    for(i=0;i<Size;i++){
        cin>>ty;
        if(ty==0) break;
        cin>>num>>name>>s1>>s2;
        switch(ty){
             case 1:pS[count++]=new GroupA(num, name, s1, s2); break;
             case 2:cin>>gs; pS[count++]=new GroupB(num, name, s1,s2, gs); break;
             case 3:cin>>s3>>s4>>s5; pS[count++]=new GroupC(num, name, s1,s2,s3,s4,s5); break;
        }            
    }
    for(i=0;i<count;i++) {
        pS[i]->display();
        delete pS[i];
    }
    return 0;
}
