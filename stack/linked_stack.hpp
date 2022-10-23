#ifndef _LINKED_STACK_CPP
#define _LINKED_STACK_CPP

#include <iostream>
#include <cassert>

template <typename T>
struct StackElement {
    T data;
    StackElement<T>* next;
};

template <typename T>
class LinkedStack {
    // Вътрешно представяне
    StackElement<T>* topPtr; // указател към връх на стека

    // Помощни методи
    void copyStack(LinkedStack const& other);
    void erase();
public:
    LinkedStack();
    LinkedStack(LinkedStack const& other);
    LinkedStack& operator=(LinkedStack const& other);
    ~LinkedStack();

    // Move семантики
    LinkedStack(LinkedStack && other);
    LinkedStack& operator=(LinkedStack && other);

    // Проверка за празнота на стек
    bool empty() const;

    // Включване на елемент 
    void push(T const& x);

    // Изключване на елемент
    void pop();

    // Извличане последно включения елемент
    T const& top() const;

    // Извличане последно включения елемент + възможност за неговата промяната
    T& top();
};

// Помощни методи
// Копиране на стек - O(n) 
template <typename T>
void LinkedStack<T>::copyStack(LinkedStack<T> const& other) {
    if (!other.topPtr) {
        topPtr = nullptr;
        return;
    }
    // other не е празен
    topPtr = new StackElement<T>{ other.topPtr->data, nullptr };
    // Помощен указател за елемент, който ще бъде копиран 
    StackElement<T>* nextToCopy = other.topPtr->next;
    // Помощен указател за последно добавен елемент
    StackElement<T>* lastAdded = topPtr;
    while (nextToCopy) {
        lastAdded = lastAdded->next = new StackElement<T>{ nextToCopy->data, nullptr };
        nextToCopy = nextToCopy->next;
    }
}

// Изтриване на паметта за стека - O(n)
template <typename T>
void LinkedStack<T>::erase() {
    while (!empty()) {
        pop();
    }
}

// Голяма четворка
template <typename T>
LinkedStack<T>::LinkedStack() {
    topPtr = nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& other) {
    copyStack(other);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& other) {
    if (this != &other) {
        erase();
        copyStack(other);
    }
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
    erase();
}

// Move семантики 
// O(1)
template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> && other) {
    topPtr = other.topPtr;
    other.topPtr = nullptr;
}

// O(1) или O(n)
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T>&& other) {
    if (this != &other) {
        erase();
        topPtr = other.topPtr;
        other.topPtr = nullptr;
    }
    return *this;
}

// Проверка за празен стек
template <typename T>
bool LinkedStack<T>::empty() const {
    return topPtr == nullptr;
}

// Добавяне на нов елемент - O(1)
template <typename T>
void LinkedStack<T>::push(T const& x) {
    // Заделяне на памет за нов елемент
    StackElement<T>* newElemPtr = new StackElement<T>;

    // Записване на стойност за този нов елемент
    newElemPtr->data = x;

    // Създаване на връзка между новия елемент и стария връх на стека (вкл. nullptr)
    newElemPtr->next = topPtr;

    // Пренасочване на върха на стека към новия елемент
    topPtr = newElemPtr;
}

// Изтриване на елемента на върха на стека - O(1)
template <typename T>
void LinkedStack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("You can not delete the top element of an empty stack!");
    }

    // Насочване на временен указател към текущия връх на стека, който следва да бъде изтрит
    StackElement<T>* tempElemPtr = topPtr;

    // Насочване на върха на стека към предходния елемент
    topPtr = topPtr->next;

    // Изтриване на върха на стека
    delete tempElemPtr;
}


// Връщане на елемента на върха на стека - O(1)
template <typename T>
T const& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return topPtr->data;
}

// Връщане на елемента на върха на стека - O(1)
template <typename T>
T& LinkedStack<T>::top() {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return topPtr->data;
}
#endif
