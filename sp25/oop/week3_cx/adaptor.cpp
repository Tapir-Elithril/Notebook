#include<iostream>
#include<stack>
#include<vector>
#include<deque>
#include<list>
using namespace std;

template<typename T>
class Stack
{
public:
    virtual ~Stack() = default;
    virtual T& top() = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual void push(const T& value) = 0;
    virtual void pop() = 0;
};

template<typename T,typename Container = std::deque<T>>
class c_stack: public Stack<T>
{
public:
    T& top() override { return c.back();}
    bool empty() const override { return c.empty(); }
    size_t size() const override { return c.size(); }
    void push(const T& value) override { c.push_back(value); }
    void pop() override { c.pop_back(); }
private:
    Container c;
};

bool is_balanced(const string &s)
{
    c_stack<char, list<char>> st;

    for(char c : s)
    {
        if(c == '{' || c == '(' || c == '[')
            st.push(c);
        else if(c == '}' || c == ')' || c == ']')
        {
            if(st.empty()) return false;
            char top = st.top();
            st.pop();

            if(c == ')' && top != '(' ||
               c == '}' && top != '{' ||
               c == ']' && top != '[')
                return false;
        }
    }
    return st.empty();
}

int main()
{
    string test1 = "a(b{c[d]e}f)g";
    string test2 = "x(y{z[)}}";

    cout << "Test 1: " << (is_balanced(test1) ? "Balanced" : "Unbalanced") << endl;
    cout << "Test 2: " << (is_balanced(test2) ? "Balanced" : "Unbalanced") << endl;
}