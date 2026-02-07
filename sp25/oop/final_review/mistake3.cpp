#include <iostream>
#include <string.h>
using namespace std;
class ERROR{};
class STRING
{
   char *m_pStr;
   int m_len;
public:
   STRING(char *str=NULL){
      if (str != NULL) {   
           m_len = strlen(str);
         m_pStr = new char[m_len+1];  
         strcpy(m_pStr,str);   
      }
      else {
         m_len = 0;
         m_pStr = NULL;
      }
   }  
   char* operator=(char *str)  
   {
      delete m_pStr ;   
      m_len = strlen(str)+1;
      m_pStr = new char[m_len]; 
      strcpy(m_pStr,str); 
      return m_pStr;  
   }
 
   bool operator==(STRING str) const
   {
      return (strcmp(m_pStr, str.m_pStr)== 0);  
   }
   char operator [] (int i) const
   {
      if (i<m_len && i>=0) return m_pStr[i];
      throw std::out_of_range("Index out of range");
   }
   char& operator[](int i) //不填
   { 
       if (i<m_len && i>=0) return m_pStr[i];
       ERROR e;
       throw e;  
   }
   friend ostream& operator<<(ostream& out ,STRING s); 
};
ostream& operator<<(ostream& out ,STRING s)     
{
   out << s.m_pStr;
   return out;  
}

int main()
{
   STRING s1,s2("HeLLO");
   int i;
   cin >> i;
   s1 = s2;
   if (s1 == s2) cout << "S1 == S2\n";
   s1[1] = s1[1] + 1;
   cout << s1 << endl;
   try
   {  
       if(s1[i]>='a' && s1[i]<='z') s1[i] =  s1[i] - 32;
       cout << s1 << endl;
   }
   catch(   ERROR& e)  
   {
      cout << "upperbound overflow";
   }
   return 0;
}   