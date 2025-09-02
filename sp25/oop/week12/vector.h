template <typename T>
class Vector {
public:
    Vector(int s):size(s) {
        content = new T[size + sss];//inline
    }
    virtual ~Vector() {
        delete[] content;
    }
    T& operator[](int i);
    //friend void f(Vector<T> &v);
private:
    T* content;
    int size;
    static int sss;
};

template <typename T>
int Vector<T>::sss = 10;

// template <typename T>
// void f(Vector<T> &v)// a declaration
// {
//     cout << v.size << endl;
// }

template <typename T>
T& Vector<T>::operator[](int i)
{
    return content[i];
}