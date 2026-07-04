#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "student.h"

using namespace std;

const string Student::courses[9] = 
{"Chinese", "Math"     , "English", 
 "Physics", "Chemistry", "Biology",
 "History", "Politics" , "Geography"};

//static member initialization
map<string, float> Student::shared_average[2];
map<string, int> Student::shared_min;
map<string, int> Student::shared_max;

void initialize_shared_values() {
     for (int i = 0; i < 9; ++i) 
     {
         Student::shared_average[0][Student::courses[i]] = 0;  
         Student::shared_average[1][Student::courses[i]] = 0;
         Student::shared_min[Student::courses[i]] = 6; 
         Student::shared_max[Student::courses[i]] = 0;
     }
 }

Student::Student() {
     // initialize every course score: 0
     for (int i = 0; i < 9; ++i)
          score[courses[i]] = 0;
}

Student::~Student() {
    //Destructor
}

void Student::input(const string& line,int no) {

     this -> no = no;
     stringstream ss(line); //create stringstream
     ss >> name; // the first word is name

     string course;
     int grade;

     while(ss >> course >> grade)
     {
          score[course] = grade;
          avaliable ++ ;
          avg += grade;
          shared_average[0][course] += grade;
          shared_average[1][course] ++;
          shared_min[course] = std::min(shared_min[course],grade);
          shared_max[course] = std::max(shared_max[course],grade);
     }
     avg /= avaliable;
}

void Student::output(){
     cout << setw(10) << left << no 
     << setw(10) << left << name;
     for (int i = 0; i < 9; i++)
          cout << setw(10) << left << (score[courses[i]] != 0 ? to_string(score[courses[i]]) : "NA");
     if(avg == 0)
          cout << setw(10) << left << "NA" << endl;
     else
          cout << setw(10) << left << avg << endl;
}

int main()
{
     initialize_shared_values();

     string line;
     vector<Student> students; // Vector to hold all student objects
     int no = 1;
 
     // Read all input
     while (getline(cin, line)) {
         Student student;
         student.input(line, no);
         students.push_back(student);  // Store the student in the vector
         no++;
     }

     cout << setw(10) << left << "no" 
          << setw(10) << left << "name";
     for(int i = 0; i < 9; i++)
          cout << setw(10) << left << Student::courses[i];
     cout << setw(10) << left << "average" << endl;

     // Output all student results after input is complete
     for (auto& student : students) // Loop through all students(type vector(auto inferred))
         student.output();

     // Output the average of each course
     cout << setw(10) << left << "" 
          << setw(10) << "average";    
     for (int i = 0; i < 9; i++) {
          if(Student::shared_average[1][Student::courses[i]] == 0)
               cout << setw(10) << "NA";
          else
               cout << setw(10) << fixed << setprecision(1) 
                    << Student::shared_average[0][Student::courses[i]] / 
                       Student::shared_average[1][Student::courses[i]];
     }
     cout << endl;

     // Output the min of each course
     cout << setw(10) << left << ""
          << setw(10) << "min";
     for (int i = 0; i < 9; i++) {
          if(Student::shared_min[Student::courses[i]] == 6)
               cout << setw(10) << "NA";
          else
               cout << setw(10) << Student::shared_min[Student::courses[i]];
     }
     cout << endl;

     // Output the max of each course
     cout << setw(10) << left << ""
          << setw(10) << "max";
     for (int i = 0; i < 9; i++) {
          if(Student::shared_max[Student::courses[i]] == 0)
               cout << setw(10) << "NA";
          else
               cout << setw(10) << Student::shared_max[Student::courses[i]];
     }
     cout << endl;

    return 0;
}
