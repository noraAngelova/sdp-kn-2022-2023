#ifndef _RESIZABLE_STACK_HPP
#define _RESIZABLE_STACK_HPP

#include <iostream>
#include <cassert>
#include "abstact_stack.hpp"


template <typename T>
class RStack : AbstractStack<T> {
private:
    T* elements;
    int topIndex;                  // Индекс на последния елемент в стека
    int capacity;                  // Капацитет на стека

    bool full() const;             // Проверка дали стек е пълен
    void resize();                 // Разширяване на стек
    void copyElements(T const*);   // Копиране на паметта на стек (до capacity)
    void eraseStack();             // Изтриване на паметта
    void copyStack(RStack const&); // Копиране на стек

public:
    RStack();
    RStack(RStack const&);
    RStack& operator=(RStack const&);
    ~RStack();

    // Move семантики
    RStack(RStack &&);
    RStack& operator=(RStack &&);

    bool empty() const;
    void push(T const& x);
    void pop();
    T top() const;
};

const unsigned INITIAL_CAPACITY = 16;

// Помощни методи
// Проверка дали стекът е пълен - O(1)
template <typename T>
bool RStack<T>::full() const {
    return topIndex == capacity - 1;
}

// Изтриване на динамично заделената памет за елементите на стека - O(1)
template <typename T>
void RStack<T>::eraseStack() {
    delete[] elements;
}

// Копиране на елементи в ПРАЗЕН стек - O(n)
template <typename T>
void RStack<T>::copyElements(T const* stackElements) {
    elements = new T[capacity];
    for (unsigned i = 0; i < capacity; i++) {
        elements[i] = stackElements[i];
    }
}

// Чисто копиране на стек - O(n)
template <typename T>
void RStack<T>::copyStack(RStack const& stack) {
    topIndex = stack.topIndex;
    capacity = stack.capacity;
    copyElements(stack.elements);
}

// Преоразмеряване - O(n)
template <typename T>
void RStack<T>::resize() {
    T* oldStackPtr = elements;
    elements = new T[2 * capacity];
    for (unsigned i = 0; i < capacity; i++) {
        elements[i] = oldStackPtr[i];
    }
    capacity *= 2;        // Удвояване на капацитета
    delete[] oldStackPtr; // Изтриване на старата памет
}


// Голяма четворка
template <typename T>
RStack<T>::RStack() : topIndex(-1), capacity(INITIAL_CAPACITY) {
    elements = new T[capacity];
}

template <typename T>
RStack<T>::RStack(RStack<T> const& stack) {
    copyStack(stack);
}

template <typename T>
RStack<T>& RStack<T>::operator=(RStack<T> const& stack) {
    if (this != &stack) {
        eraseStack();
        copyStack(stack);
    }
    return *this;
}

template <typename T>
RStack<T>::~RStack() {
    eraseStack();
}

// Move семантики
// O(1)
template <typename T>
RStack<T>::RStack(RStack&& other) {
    topIndex = other.topIndex;
    capacity = other.capacity;

    elements = other.elements;
    other.elements = nullptr;
}

// O(n)
template <typename T>
RStack<T>& RStack<T>::operator=(RStack<T>&& other) {
    if (this != &other) {
        topIndex = other.topIndex;
        capacity = other.capacity;
        
        eraseStack();
        elements = other.elements;
        other.elements = nullptr;
    }

    return *this;
}

// Проверка дали стекът е празен - O(1)
template <typename T>
bool RStack<T>::empty() const {
	return topIndex == -1;
}

// Изтриване на елемента на върха на стека - O(1)
template <typename T>
void RStack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("You can not delete the top element of an empty stack!");
    }

    topIndex--;
}

// Извличане на върха на стека - O(1)
template <typename T>
T RStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return elements[topIndex];
}

// Добавяне на елемент на върха на стека
// O(1) или O(n)
template <typename T>
void RStack<T>::push(T const& x) {
    if (full()) {
        resize();
    }
    elements[++topIndex] = x;
}
#endif
