#ifndef _LINKED_QUEUE_HPP
#define _LINKED_QUEUE_HPP

template <typename T>
struct QueueElement {
	T data;
	QueueElement<T>* next;
};

template <typename T>
class LinkedQueue {
private:
	QueueElement<T> *front, *back;

	void copyQueue(LinkedQueue<T> const&);
	void erase();
public:
	LinkedQueue();
	LinkedQueue(LinkedQueue<T> const&);
	LinkedQueue& operator=(LinkedQueue<T> const&); 
	~LinkedQueue();

    // Move семантики
	LinkedQueue(LinkedQueue<T> &&);
	LinkedQueue& operator=(LinkedQueue<T> &&); 

	bool empty() const;
	void push(T const& x);
	void pop();
	T& head();
	T const & head() const;
};

// Помощни методи
// Чисто копиране на опашка - O(n)
template <typename T>
void LinkedQueue<T>::copyQueue(LinkedQueue<T> const& other) {
    if (other.empty) {
        front = back = nullptr;
    }
    
    QueueElement<T>* elemPtr = other.front;
    while (elemPtr) {
        push(elemPtr->data);
        elemPtr = elemPtr->next;
    }
}

// Изтриване на опашка - O(n)
template <typename T>
void LinkedQueue<T>::erase() {
    while (!empty()) {
        pop();
    }
}

// Голяма четворка
template <typename T>
LinkedQueue<T>::LinkedQueue() : front(nullptr), back(nullptr) {}

template <typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T> const& other) {
    copyQueue(other);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T> const& other) {
    if (this != &other) {
        erase();
        copyQueue(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    erase();
}

// Move семантики
template <typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T>&& other) {
    front = other.front; 
    back = other.back;
    other.front = nullptr;
    other.back = nullptr;
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other) {
    if (this != &other) {
        erase();

        front = other.front;
        back = other.back;
        other.front = nullptr;
        other.back = nullptr;
    }
}

// Сложност O(1)
template <typename T>
bool LinkedQueue<T>::empty() const {
    return (front == nullptr && back == nullptr);
}

// Сложност O(1)
template <typename T>
void LinkedQueue<T>::push(T const& newElemData) {
    QueueElement<T>* newElemPtr = new QueueElement<T>{ newElemData, nullptr };

    if (!empty()) {
        // Опашката не е празна и елементът се слага като последен
        back->next = newElemPtr;
    }
    else {
        // Опашката е празна и елементът трябва да бъде в началото
        front = newElemPtr;
    }

    back = newElemPtr;
}

// Сложност O(1)
template <typename T>
void LinkedQueue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Can not delete element from an empty queue");
    }

    QueueElement<T>* delElemPtr = front;
 
    // Премества се указателя към следващия елемент в опашката
    front = front->next;

    // Няма друг елемент в опашката и back трябва да бъде nullptr
    if (front == nullptr) {
        back = nullptr;
    }
    // Изтрива се заделената памет за елемента
    delete delElemPtr;
}

// Връща първия елемент на опашката - O(1)
template <typename T>
T& LinkedQueue<T>::head() {
    if (empty()) {
        throw std::runtime_error("The queue is empty!");
    }

    return front->data;
}

// Връща първия елемент на опашката - O(1)
template <typename T>
T const& LinkedQueue<T>::head() const {
    if (empty()) {
        throw std::runtime_error("The queue is empty!");
    }

    return front->data;
}

#endif
