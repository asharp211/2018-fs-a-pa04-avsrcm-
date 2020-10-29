/* Define all your MyVector-related functions here.
 * You do not need to include the h file.
 * It included this file at the bottom.
 */
#include "MyVector.h"

void get_identity(string my_id[])
{
    my_id[0] = "avsrcm";
    my_id[1] = "12449123";
}

template <typename T>
void swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T>
MyVector<T>::MyVector()
{
    m_data = nullptr;
    reserved_size = 0;
    data_size = 0;
}

// We're giving you this one for free
// and as a guide for the syntax.
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] m_data;
}

// Another example: remember when writing an implementation in hpp,
// return type first, then scope just before the function name.
template <typename T>
T & MyVector<T>::at(int index)
{
    //Define the function here.
    if( index < 0 || index >= data_size)
        throw std::out_of_range("Out of range");
    else
        return m_data[index];
}

// Make sure this does a deep copy
template <typename T>
MyVector<T> & MyVector<T>::operator=(const MyVector<T> &source)
{
    if(data_size != source.data_size)
    {
        T vectorSize = new T[source.data_size];
        data_size = source.data_size;
    }

    for(int i = 0; i < data_size; i++)
    {
        m_data[i] = source.m_data[i];
    }
}

// Make sure this does a deep copy.
template <typename T>
MyVector<T>::MyVector(const MyVector<T> &source)
{
    if(data_size < 0)
    {
        delete m_data;
    }

    m_data = new T[source.data_size];

    data_size = source.data_size;

    reserved_size = source.reserved_size;
}

// Returns the element of the array by reference, so it can be read or written.
template <typename T>
T & MyVector<T>::operator[](int i)
{
    return m_data[i];
}

// Purpose: Returns the element stored at the front of the vector
template <typename T>
T & MyVector<T>::front()
{
        return m_data[0];
}
// Purpose: Returns the element stored at the back of the vector
template <typename T>
T & MyVector<T>::back()
{
    m_data[data_size - 1];
}
// Purpose: Returns the maximum number of elements that can be stored in the current Vector
template <typename T>
int MyVector<T>::capacity()
{
    return reserved_size;
}
// Purpose: Ensures that there is enough room for a specific number of elements
// Parameters: new_cap - The amount of space to be reserved in the array.
// Postconditions: Increases max_size to new_cap if new_cap > max_size
// Other functions should check that their operations are not going beyond the size limit,
// and call this one if so
// By default, you should double the size of the current array when it fills up.
// NOTE: reserve does not do the checking of whether it's full; another function should
// do that, and then call reserve, which just adjusts the size to whatever it is called with,
// only if it is greater than current.
// Inital size is 0, so a special case is needed to grow to 1, then 2, 4, etc.,
template <typename T>
void MyVector<T>::reserve(int new_cap)
{
    if(data_size == new_cap)
    {
        return;
    }

    T *max_size = new T[new_cap];

    if(reserved_size > new_cap)
    {
        new_cap = reserved_size;
    }
    for(int i = 0; i < data_size; i++)
    {
        max_size[i] = m_data[i];
    }

    delete [] max_size;
    delete[] m_data;
    m_data = new T[new_cap];
    reserved_size = new_cap;
}

// If your array hits the point at which it is less than (not <=)
// 1/4 full, it should call this function.
// It should shrink such that the array is 2x as big as the data.
// NOTE: shrink_to_fit does not do the checking of 1/4 full;
// another function should do that, and then call shrink_to_fit.
template <typename T>
void MyVector<T>::shrink_to_fit()
{
     T *hold[] = new T [data_size*2];

    if(!data_size <= data_size*0.25)
    {
        data_size = data_size*.25;
    }
    for(int h = 0; h < reserved_size; h++)
    {
        hold[h] = m_data[h];
    }

}

// Fills the array with count of T value (e.g., 5 a would be [a, a, a, a, a])
// This replaces the current array.
template <typename T>
void MyVector<T>::assign(int count, const T &value)
{
    while(m_data > data_size)
    {
        *m_data = value;
        m_data++;
        count--;
    }
}

// Purpose: Clears the MyVector
// Postconditions: current size set to 0, storage size to default (0).
// elements are deallocated and data is set to nullptr
template <typename T>
void MyVector<T>::clear()
{
    if(m_data != nullptr)
    {
        data_size = 0;
        reserved_size = 1;

        delete [] m_data;
        m_data = nullptr;
    }
}

// Purpose: appends the value x to the end of an MyVector
// Parameters: x is value to be added to MyVector
// Postconditions: current size is incremented by 1
// If max size is reached, the storage array is grown.
template <typename T>
void MyVector<T>::push_back(const T &x)
{
    if(reserved_size <= 0)
    {
        reserve(1);
    }
    if(data_size + 1 <= reserved_size)
    {
        m_data[data_size] = x;
        data_size++;
    }
    else
    {
        reserve(reserved_size * 2);
        m_data[data_size] = x;
        data_size++;
    }
}

// Removes the last element of the vector
template <typename T>
void MyVector<T>::pop_back()
{
    if(m_data[data_size] > 0)
        data_size--;
}

// Purpose: inserts the value x at the position i
// (before the value currently at i) in the  MyVector
// Parameters: x is value to be added to MyVector
// i is the position to insert x at
// Post conditions: current size is incremented by 1
// If max size is reached, the storage array is grown.
template <typename T>
void MyVector<T>::insert(int i, const T &x)
{
    if(data_size == reserved_size)
    {
      reserve(reserved_size * 2);
    }
    for(int j = data_size; j < i; j++)
    {
        m_data[j] = m_data[j + 1];
    }
    m_data[i] = x;
    data_size++;
}

// Purpose: Removes the element at index i in the array
// Parameters: i, the index of the element to remove
// Post conditions: if the size of the list is greater than 0
// size is decremented by one.
// if the size of the list less than 1/4 the max size,
// the storage array is shrunk.
template <typename T>
void MyVector<T>::erase(int i)
{
    for(int j = data_size; j < i; j++)
    {
        m_data[j] = m_data[i+1];
    }
    data_size--;
    if(data_size <= reserved_size*0.25)
    {
        shrink_to_fit();
    }

}

// Returns the size of the actual data stored in the array list
// Remember, with indexing at 0, this is 1 more than the last elements position index
template <typename T>
int MyVector<T>::size()
{
    return data_size;
}
