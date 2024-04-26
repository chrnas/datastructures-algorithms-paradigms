/*
 * TDDD86 Fisher
 * This file contains the declaration and implementation of MyPriorityQueue.
 *
 */

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    /**
     * @brief This function puts the parameter (t) at the end of the vector.
     * @param t
     */
    void push(const T& t);

    /**
     * @brief Returns the first element in the vector.
     * @return
     */
    T top()const;

    /**
     * @brief Removes the first element and reorganizes the PriorityQueue
     */
    void pop();

    /**
     * @brief swap swaps positions of elements with index one and two.
     * @param one integer representing the index of the elment that will have its position swapped with the element with index two.
     * @param two integer representing the index of the elment that will have its position swapped with the element with index one.
     */
    void swap(int one, int two);

    /**
     * @brief checks if MyPriorityQueue is enmpy
     * @return returns a boolean, true if empty otherwise false.
     */
    bool empty()const;

    /**
     * @brief size returns an integer representing the number of elements of MyProrityQueue
     */
    unsigned size() const;

private:
    MyVector<T> vector_array;
    C strictly_larger_operator;
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    for(int i = vector_array.size()-1; i > 0; i = (i-1)/2){
        if(strictly_larger_operator(vector_array[(i-1)/2], vector_array[i])){
            swap((i-1)/2, i);
        }
        else{
            break;
        }
    }
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::swap(int one, int two){
    T temptop = vector_array[one];
    vector_array[one] = vector_array[two];
    vector_array[two] = temptop;
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    swap(0, vector_array.size()-1);
    vector_array.pop_back();
    int index = 0;

    while(true){
        unsigned left = 2*index+1;
        unsigned right = 2*index +2;
        if(left>=vector_array.size()){
            break;
        }
        int child = left;
        if(right < vector_array.size() && strictly_larger_operator(vector_array[left], vector_array[right])){
            child = right;
        }
        if(strictly_larger_operator(vector_array[child], vector_array[index])){
            break;
        }
        swap(index, child);
        index = child;
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
