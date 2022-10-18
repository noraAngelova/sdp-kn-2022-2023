#ifndef _STATIC_STACK_HPP
#define _STATIC_STACK_HPP

#include <iostream>
#include <cassert>
#include "abstact_stack.hpp"

const int MAX_SIZE = 1024;

template <typename T>
class Stack : public AbstractStack<T> {
private:
    T elements[MAX_SIZE];  // �������� �����������
    int topIndex;          // ������ �� ����� �� �����

    bool full() const;     // ������� ������� �� �����������
public:
    Stack();               // ��������� �� ������ ����

    bool empty() const;    // �������� ���� ���� � ������
    void push(T const& x); // ��������� �� �������
    void pop();               // ���������� �� �������
    T top() const;         // ������ �� ����� �� �����
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
