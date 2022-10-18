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
    // �������� �����������
    StackElement<T>* topPtr; // �������� ��� ���� �� �����

    // ������� ������
    void copy(LinkedStack const& ls);
    void erase();
public:
    // ��������� �� ������ ����
    LinkedStack();

    // ����������� �� ��������
    LinkedStack(LinkedStack const& ls);

    // �������� �� �����������
    LinkedStack& operator=(LinkedStack const& ls);

    // ����������
    ~LinkedStack();

    // move?

    // �������� �� �������� �� ����
    bool empty() const;

    // ��������� �� ������� 
    void push(T const& x);

    // ���������� �� �������
    T pop();

    // ��������� �������� ��������� �������
    T const& top() const;

    // ��������� �������� ��������� ������� + ���������� �� �������� ���������
    T& top();
};

// ��������� �� ������ ����
template <typename T>
LinkedStack<T>::LinkedStack() {
    topPtr = nullptr;
}

// �������� �� ������ ����
template <typename T>
bool LinkedStack<T>::empty() const {
    return topPtr == nullptr;
}

// �������� �� ���� 
// ������� 3 - ���� ���������� �� ������������ ����
template <typename T>
void LinkedStack<T>::copy(LinkedStack<T> const& ls) {
    topPtr = nullptr;

    StackElement<T>* p = ls.topPtr;
    LinkedStack<T> tmp;
    while (p != nullptr) {
        tmp.push(p->data);
        p = p->next;
    }
    while (!tmp.empty())
        push(tmp.pop());
}

// ��������� �� ������� �� �����
template <typename T>
void LinkedStack<T>::erase() {
    // !!! delete topPtr;
    while (!empty()) {
        pop();
    }
}

// ����������� �� ��������
template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls) {
    copy(ls);
}

// ����������
template <typename T>
LinkedStack<T>::~LinkedStack() {
    erase();
}

// �������� �� ����������� ����� ��� �����
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack<T> const& ls) {
    if (this != &ls) {
        erase();
        copy(ls);
    }
    return *this;
}

// �������� �� ��� �������
template <typename T>
void LinkedStack<T>::push(T const& x) {
    // �������� �� ����� �� ��� �������
    StackElement<T>* newElemPtr = new StackElement<T>;

    // ��������� �� �������� �� ���� ��� �������
    newElemPtr->data = x;

    // ��������� �� ������ ����� ����� ������� � ������ ���� �� ����� (���. nullptr)
    newElemPtr->next = topPtr;

    // ������������ �� ����� �� ����� ��� ����� �������
    topPtr = newElemPtr;
}

// ��������� �� �������� �� ����� �� �����
template <typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        std::cerr << "Stack is empty" << std::endl;
        return T();
    }

    T result = top();

    // ��������� �� �������� �������� ��� ������� ���� �� �����, ����� ������ �� ���� ������
    StackElement<T>* tempElemPtr = topPtr;

    // ��������� �� ����� �� ����� ��� ���������� �������
    topPtr = topPtr->next;

    // ��������� �� ����� �� �����
    delete tempElemPtr;

    return result;
}

template <typename T>
T const& LinkedStack<T>::top() const {
    assert(!empty());
    
    return topPtr->data;
}

template <typename T>
T& LinkedStack<T>::top() {
    assert(!empty());

    return topPtr->data;
}

#endif