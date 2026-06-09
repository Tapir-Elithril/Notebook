#include<iostream>
#include<map>
using namespace std;

int main()
{
    map<string, int> word_map;
    for(const auto& w:{"we","are","not","humans","we","are","robots","!!"})
        word_map[w]++;

    for(const auto& [word,count]:word_map)
        cout << count << " occurrences of word '" << word << "'" << endl;
}