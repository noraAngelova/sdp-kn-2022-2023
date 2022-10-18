#ifndef _RESIZABLE_STACK_HPP
#define _RESIZABLE_STACK_HPP

#include <iostream>
#include <cassert>

template <typename T>
class RStack {
private:
    T* arr;
    int topIndex;                  // Индекс на последния елемент в стека
    int capacity;                  // Капацитет на стека

    bool full() const;             // Проверка дали стек е пълен
    void resize();                 // Разширяване на стек
    void copy(T const*);           // Копиране на паметта на стек (до capacity)
    void eraseStack();             // Изтриване на паметта
    void copyStack(RStack const&); // Копиране на стек

public:
    RStack();
    RStack(RStack const&);
    RStack& operator=(RStack const&);
    ~RStack();

    bool empty() const;
    void push(T const& x);
    T pop();
    T top() const;
};

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
RStack<T>::RStack() : topIndex(-1), capacity(INITIAL_CAPACITY) {
	arr = new T[capacity];
}

template <typename T>
bool RStack<T>::empty() const {
	return topIndex == -1;
}

template <typename T>
bool RStack<T>::full() const {
	return topIndex == capacity - 1;
}

template <typename T>
T RStack<T>::pop() {
    if (empty()) {
        std::cerr << "Изключване на елемент от празен стек!\n";
        return T();
    }
    return arr[topIndex--];
}

template <typename T>
T RStack<T>::top() const {
    if (empty()) {
        std::cerr << "Достъп до върха на празен стек!\n";
        return T();
    }
    return arr[topIndex];
}

template <typename T>
void RStack<T>::eraseStack() {
    delete[] arr;
}

template <typename T>
RStack<T>::~RStack() {
    eraseStack();
}

template <typename T>
void RStack<T>::push(T const& x) {
    if (full()) {
        resize();
    }
    arr[++topIndex] = x;
}

template <typename T>
void RStack<T>::copy(T const* stackArr) {
    for (unsigned i = 0; i < capacity; i++) {
        arr[i] = stackArr[i];
    }
}

template <typename T>
void RStack<T>::copyStack(RStack const& stack) {
    topIndex = stack.topIndex;
    capacity = stack.capacity;
    arr = new T[capacity];
    copy(stack.arr);
}

template <typename T>
void RStack<T>::resize() {
    T* oldStackPtr = arr;
    arr = new T[2 * capacity];
    copy(oldStackPtr);
    capacity *= 2;        // Удвояване на капацитета
    delete[] oldStackPtr; // Изтриване на старата памет
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

#endif