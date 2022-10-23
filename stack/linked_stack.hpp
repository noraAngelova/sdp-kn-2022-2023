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
    void copyStack(LinkedStack const& ls);
    void erase();
public:
    // Създаване на празен стек
    LinkedStack();

    // Конструктор за копиране
    LinkedStack(LinkedStack const& ls);

    // Операция за присвояване
    LinkedStack& operator=(LinkedStack const& ls);

    // Деструктор
    ~LinkedStack();

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

// Голяма четворка
template <typename T>
LinkedStack<T>::LinkedStack() {
    topPtr = nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls) {
    copyStack(ls);
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
    if (this != &ls) {
        erase();
        copyStack(ls);
    }
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
    erase();
}


// Проверка за празен стек
template <typename T>
bool LinkedStack<T>::empty() const {
    return topPtr == nullptr;
}

// Копиране на стек 
// Вариант 3 - чрез използване на допълнителен стек
template <typename T>
void LinkedStack<T>::copyStack(LinkedStack<T> const& ls) {
    topPtr = nullptr;

    StackElement<T>* p = ls.topPtr;
    LinkedStack<T> tmp;
    while (p != nullptr) {
        tmp.push(p->data);
        p = p->next;
    }
    while (!tmp.empty()) {
        push(tmp.top());
        tmp.pop();
    }
}

// Изтриване на паметта за стека
template <typename T>
void LinkedStack<T>::erase() {
    // !!! delete topPtr;
    while (!empty()) {
        pop();
    }
}

// Добавяне на нов елемент
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

// Изтриване на елемента на върха на стека
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

template <typename T>
T const& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }
    
    return topPtr->data;
}

template <typename T>
T& LinkedStack<T>::top() {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return topPtr->data;
}

#endif
