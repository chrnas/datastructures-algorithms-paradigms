/*
 * TDDD86 Fisher
 * This file contains the declaration and implementation of MyVector.
 *
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);

    /**
     * @brief Adds element to MyVector at last index. Increases capacity if needed.
     */
    void push_back(const T&);

    /**size
     * @brief removes the element of MyVector with the last index. Decreases capacity if needed.
     */
    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    /**
     * @brief empty Check if MyVector is empty.
     * @return boolean true if empty, otherwise fasle.
     */
    bool empty()const;

    /**
     * @brief begin returns a pointer to the first element of the MyVector.
     * @return A pointer to the first elem of the MyVector.
     */
    T* begin();

    /**
     * @brief begin returns a pointer to the last element of the MyVector.
     * @return A pointer to the first element of the MyVector.
     */
    T* end();

    /**
     * @brief clear Removes all elements of MyVector and resets capacity of MyVector to 1.
     */
    void clear();

    /**
     * @brief size returns an integer representing the number of elements of MyVector.
     */
    unsigned size()const;

private:
    unsigned capacity = 0;
    unsigned numberOfElements;
    T* storage;

};

template<typename T>
MyVector<T>::MyVector(){
    capacity = 1;
    numberOfElements = 0;
    storage = new T[1];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    numberOfElements = other.size();
    capacity = other.capacity;
    storage = new T[capacity];
    for(unsigned number = 0; number < numberOfElements; number++){
        storage[number] = other[number];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(this != &other){
        numberOfElements = other.size();
        capacity = numberOfElements * 2 + 1;
        delete[] storage;
        storage = new T[capacity];
        for(unsigned number = 0; number < numberOfElements; number++){
            storage[number] = other[number];
        }
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if(capacity != 0){
        if(numberOfElements == capacity){
            capacity *= 2;
            T* temp = new T[capacity];
            for(unsigned number = 0; number < numberOfElements; number++){
                temp[number] = storage[number];
            }
            delete[] storage;
            storage = temp;
        }
        storage[numberOfElements] = e;
        numberOfElements++;
    }
}

template<typename T>
void MyVector<T>::pop_back(){
    if(numberOfElements >= 1){
        numberOfElements--;
        if(numberOfElements <= capacity/2){
            capacity /= 2;
            T* temp = new T[capacity];
            for(unsigned number = 0; number < numberOfElements; number++){
                temp[number] = storage[number];
            }
            delete[] storage;
            storage = temp;
        }
    }
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    if(i < capacity){
        return storage[i];
    }
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    if(i < capacity){
        return storage[i];
    }
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    if(capacity != 0){
        capacity = 1;
        numberOfElements = 0;
        delete[] storage;
        storage = new T[capacity];
    }
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

template<typename T>
T* MyVector<T>::end(){
    return (storage + numberOfElements);
}

#endif // MY_VECTOR_H
