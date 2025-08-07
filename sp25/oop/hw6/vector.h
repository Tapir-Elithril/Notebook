#ifndef _VECTOR__H
#define _VECTOR__H
#include <stdexcept>

using namespace std;

template <typename T>
class Vector {
public:
  Vector();                      // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index);      // accesses the specified element without bounds checking
  T& at(int index);              // accesses the specified element, throws an exception of
                                 // type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;              // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty 
private:
  void inflate();                // expand the storage of the container to a new capacity,
                                 // e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the total number of elements that can be held in the
                                 // allocated storage
};

template <typename T>
Vector<T>::Vector():m_pElements(nullptr),m_nSize(0),m_nCapacity(0){
}

template <typename T>
Vector<T>::Vector(int size):m_nSize(size),m_nCapacity(size){
  m_pElements = new T[size];
}

template <typename T>
Vector<T>::Vector(const Vector& r):m_nSize(r.m_nSize),m_nCapacity(r.m_nCapacity),m_pElements(new T[r.m_nCapacity])
{ 
  //deep copy,otherwise the two vectors may share the same memory  
  for(int i = 0; i < m_nSize; ++i)
    m_pElements[i] = r.m_pElements[i];
}

template <typename T>
Vector<T>::~Vector(){
  delete[] m_pElements;
}

template <typename T>
T& Vector<T>::operator[](int index)
{
  return m_pElements[index];
}

template <typename T>
T& Vector<T>::at(int index)
{
  if(index < 0 || index >= m_nSize)
  {
    throw std::out_of_range("Vector::at() index out of range");
  }
  return m_pElements[index];
}

template <typename T>
int Vector<T>::size() const {
  return m_nSize;
}

template <typename T>
void Vector<T>::push_back(const T& x)
{
  if (m_nSize >= m_nCapacity)
    inflate();
  m_pElements[m_nSize] = x;  
  m_nSize++;               
}

template <typename T>
void Vector<T>::clear()
{
  //clear the elements but dont destroy the vector 
  for(int i = 0; i < m_nSize; ++i)
    m_pElements[i].~T(); //call the destructor apparently,can also deal with int,double,...
  m_nSize = 0;
}

template <typename T>
bool Vector<T>::empty() const {
  return m_nSize == 0;
}

template <typename T>
void Vector<T>::inflate() {
  //if current capacity == 0,give it an initial space of 1 * sizeof(T)
  int newCapacity = (m_nCapacity == 0) ? 1 : 2 * m_nCapacity;
  //space allocation
  T* newElements = new T[newCapacity];
  //copy
  for(int i = 0;i < m_nSize; ++i)
    newElements[i] = m_pElements[i];
  delete[] m_pElements;
  m_pElements = newElements;
  m_nCapacity = newCapacity;
  //size no need to change
}

#endif