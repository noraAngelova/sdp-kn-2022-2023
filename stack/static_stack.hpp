#ifndef _STATIC_STACK_HPP
#define _STATIC_STACK_HPP

#include <iostream>
#include <cassert>
#include "abstact_stack.hpp"

const int MAX_SIZE = 1024;

template <typename T>
class Stack : public AbstractStack<T> {
private:
    T elements[MAX_SIZE];  // Вътрешно представяне
    int topIndex;          // Индекс на върха на стека

    bool full() const;     // Помощна функция за запълненост
public:
    Stack();               // Създаване на празен стек

    bool empty() const;    // Проверка дали стек е празен
    void push(T const& x); // Включване на елемент
    void pop();               // Изключване на елемент
    T top() const;         // Достъп до върха на стека
};

template <typename T>
Stack<T>::Stack() : topIndex(-1) {}

template <typename T>
bool Stack<T>::empty() const {
	return topIndex == -1;
}

template <typename T>
bool Stack<T>::full() const {
	return topIndex == MAX_SIZE - 1;
}

template <typename T>
void Stack<T>::push(T const& x) {
    if (full()) {
        std::cerr << "The stack is full!\n";
    }
    else {
        elements[++topIndex] = x;
    }
}

template <typename T>
void Stack<T>::pop() {
    assert(!empty());
    return elements[topIndex--];
}

template <typename T>
T Stack<T>::top() const {
    assert(!empty());
    return elements[topIndex];
}

#endif
