#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>  //setting precision

using namespace std;

int main()
{
    //cout << "no      name    score1  score2  score3  average" << endl;
    cout << setw(8) << left << "no" 
         << setw(8) << left << "name"
         << setw(8) << left << "score1"
         << setw(8) << left << "score2"
         << setw(8) << left << "score3"
         << setw(8) << left << "average" << endl;
     //setw(8):set width of the field to 8 characters
     //left: left-justified

    ifstream file("score.txt");

    if (!file.is_open())
    {
        cout << "File not found" << endl;
        return 1;
    }
    //check whether file exists

    int no = 1;
    string name;
    int score1, score2, score3;
    float average;
    int totalScore1 = 0, totalScore2 = 0, totalScore3 = 0;
    int minScore1 = 5, minScore2 = 5, minScore3 = 5;
    int maxScore1 = 1, maxScore2 = 1, maxScore3 = 1;
    int count = 0;

    while (file >> name >> score1 >> score2 >> score3)
    {
        average = (score1 + score2 + score3) / 3.0;
        
        totalScore1 += score1;
        totalScore2 += score2;
        totalScore3 += score3;

        minScore1 = min(minScore1, score1);
        minScore2 = min(minScore2, score2);
        minScore3 = min(minScore3, score3);
        maxScore1 = max(maxScore1, score1);
        maxScore2 = max(maxScore2, score2);
        maxScore3 = max(maxScore3, score3);

    cout << setw(8) << left << no 
         << setw(8) << left << name
         << setw(8) << left << score1
         << setw(8) << left << score2
         << setw(8) << left << score3
         << setw(8) << left << average << endl;

        no++;
        count++;
    }

    float avgScore1 = totalScore1 / float(count);
    float avgScore2 = totalScore2 / float(count);
    float avgScore3 = totalScore3 / float(count);

    cout << setw(8) << left << "" 
         << setw(8) << "average"    
         << setw(8) << fixed << setprecision(1) << avgScore1
         << setw(8) << fixed << setprecision(1) << avgScore2
         << setw(8) << fixed << setprecision(1) << avgScore3 << endl;
     //setprecision(1): set the precision of the floating point number to 1 decimal place

    cout << setw(8) << left << ""
         << setw(8) << "min"
         << setw(8) << minScore1
         << setw(8) << minScore2
         << setw(8) << minScore3 << endl;

    cout << setw(8) << left << ""
         << setw(8) << "max"
         << setw(8) << maxScore1
         << setw(8) << maxScore2
         << setw(8) << maxScore3 << endl;

    file.close();
    return 0;
}
