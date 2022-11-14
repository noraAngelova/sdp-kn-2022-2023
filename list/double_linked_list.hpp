#ifndef _DLLIST_HPP
#define _DLLIST_HPP

template <typename T>
struct DoubleLinkedListElement {
    T data;
    DoubleLinkedListElement<T> *next, *prev;
};

// Декларация на свързан списък с две връзки
template <typename T>
class DoubleLinkedList;

// Итератор за свързан списък с две връзки
template <typename T>
class DoubleLinkedListIterator {
    // Осигураване на достъп до елементите на свързан списък
    friend class DoubleLinkedList<T>;

    // Съкращение, което ще се използва за тип елементите, които ще обхождаме
    using DLLE = DoubleLinkedListElement<T>;

    // Тип итератор
    using I = DoubleLinkedListIterator<T>;

    // Указател към елемент на свързания списък, който ще се използва за абстракция на позиция
    DLLE *ptr;
public:
    // Конструктор за итератор - абстракция на позиция в свързан списък с две връзки
    DoubleLinkedListIterator(DLLE* p = nullptr) : ptr(p) {}

    // Проверка за валидност на итератора/позицията.
    bool valid() const { 
        return ptr != nullptr; 
    }

    // Преместване към следваща елемент. Връща се новата позиция (итератор)
    I next() const {
        if (!valid())
            return *this;

        return I(ptr->next);
    }

    I prev() const {
        if (!valid())
            return *this;

        return I(ptr->prev);
    }

    // ! Не се прави валидация. Предоставен е метод за проверка на валидност
    T const& getConst() const {
        return ptr->data;
    }
    T& get() const {
        return ptr->data;
    }

    // Синтактична захар
    // Начин на използване: it <-> it.valid();
    operator bool() const { 
        return valid(); 
    }

    // Начин на използване: ++it
    I& operator++() {
        return (*this = next());
    }

    // Начин на използване: it++
    I operator++(int) {
        I save = *this;
        ++(*this); // Променя позицията, която се намира в *this
        return save;
    }

    // Начин на използване: --it
    I& operator--() {
        return (*this = prev());
    }

    // Начин на използване: it--
    I operator--(int) {
        I save = *this;
        --(*this);
        return save;
    }

    // Начин на използване: *it = 3;
    T& operator*() {
        return get();
    }

    bool operator==(I const& it) const {
        return ptr == it.ptr;
    }
    bool operator!=(I const& it) const {
        return !(*this == it);
    }

    I& operator+=(unsigned n) {
        for (unsigned i = 0; i < n; i++) {
            ++(*this);
        }
        return *this;
    }

    I& operator-=(unsigned n) {
        for (unsigned i = 0; i < n; i++) {
            --(*this);
        }
        return *this;
    }
};

// Реализация на свързан списък с две връзки
template <typename T>
class DoubleLinkedList {
    using DLLE = DoubleLinkedListElement<T>;
    DLLE *front, *back;

    void erase();
public:
    using I = DoubleLinkedListIterator<T>;

    DoubleLinkedList() : front(nullptr), back(nullptr) {}

    DoubleLinkedList(DoubleLinkedList const& ll);
    DoubleLinkedList& operator=(DoubleLinkedList const& ll);
    ~DoubleLinkedList() { 
        erase(); 
    }

    // Move семантики

    bool empty() const {
        return front == nullptr && back == nullptr;
    }

    // Базови методи на класа
    bool insertBefore(I const& it, T const& x);
    bool insertAfter(I const& it, T const& x);

    bool deleteBefore(I const& it, T& x);
    bool deleteAt(I const& it, T& x);
    bool deleteAfter(I const& it, T& x);

    // Допълнителни методи
    bool deleteBefore(I const& it) {
        T tmp;
        return deleteBefore(it, tmp);
    }

    bool deleteAt(I const& it) {
        T tmp;
        return deleteAt(it, tmp);
    }

    bool deleteAfter(I const& it) {
        T tmp;
        return deleteAfter(it, tmp);
    }

    bool insertFirst(T const& x) {
        return insertBefore(begin(), x);
    }
    bool insertLast(T const& x) {
        return insertAfter(end(), x);
    }

    bool deleteFirst(T& x) {
        return deleteAt(begin(), x);
    }
    bool deleteLast(T& x) {
        return deleteAt(end(), x);
    }

    bool deleteFirst() {
        return deleteAt(begin());
    }
    bool deleteLast() {
        return deleteAt(end());
    }

    T const& getAt(I const& it) const {
        return it.getConst();
    }
    T& getAt(I const& it) {
        return it.get();
    }

    // Метод, който връща итератор към първия елемент
    I begin() const {
        return I(front);
    }
    // Метод, който връща итератор към края на списъка
    I end() const {
        return I();
    }
    // Метод, който връща итератор към последния елемент
    I last() const {
        return I(back);
    }

    // Залепва елементите на l в края на списъка
    void append(DoubleLinkedList const& l);

    // Присвоява си елементите на l като ги залепва в края на списъка
    void appendAssign(DoubleLinkedList& l);

    // Синтактична захар
    // Предефиниране на оператор += за добавяне на елемент към края на свързания списък
    DoubleLinkedList<T>& operator+=(T const& x) {
        insertLast(x);
        return *this;
    }
};

// O(1) по време и по памет
template <typename T>
bool DoubleLinkedList<T>::insertAfter(I const& it, T const& x) {
    // Проверка дали списъкът е празен 
    if (empty()) {
        // Добавя се нов и единствен елемент в списъка
        // { data, next, prev }
        front = back = new DLLE{ x, nullptr, nullptr };
        return true;
    }

    // Списъкът не е празен
    // !it - ако добавяме елемент на позиция end() (след края)
    // it.ptr == back - ако добавяме елемент след последния
    if (!it || it.ptr == back) {
        // Добавяме след края на списъка {стойност, next, prev}
        back = new DLLE{ x, nullptr, back };
        back->prev->next = back;
        return true;
    }

    // it.ptr != nullptr
    // it.ptr->next != nullptr
    DLLE *newElem = new DLLE{ x, it.ptr->next, it.ptr };
    newElem->next->prev = newElem;
    newElem->prev->next = newElem;
    return true;
}

// O(1) по време и по памет
template <typename T>
bool DoubleLinkedList<T>::insertBefore(I const& it, T const& x) {
    if (empty())
        return insertLast(x);

    // вмъкване преди първи елемент
    if (it.ptr == front ||    // посочили сме за итератор първия елемент
        (!it && back->prev == nullptr)) {  // искаме да вмъкваме преди последния елемент, но имаме само един елемент!
        // добавяме преди началото на списъка
        front = new DLLE{ x, front, nullptr };
        front->next->prev = front;
        return true;
    }

    // не вмъкваме преди първи елемент
    if (!it)
        // искаме да вмъкваме преди последния елемент
        return insertAfter(I(back->prev), x);

    // общ случай
    return insertAfter(it.prev(), x);
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteAt(I const& it, T& x) {
    // ако it.ptr е nullptr, значи имаме предвид back
    DLLE* toDelete = it ? it.ptr : back;

    if (toDelete == nullptr) {
        // опит за изтриване в празен списък!
        return false;
    }

    // Има ли предходен елемент
    if (toDelete->prev != nullptr) {
        toDelete->prev->next = toDelete->next;
    }
    else {
        // изтриваме първия елемент, трябва да преместим front
        front = toDelete->next;
    }

    // Има ли следващ елемент
    if (toDelete->next != nullptr) {
        toDelete->next->prev = toDelete->prev;
    }
    else {
        // Изтриваме последния елемент, трябва да преместим back
        back = toDelete->prev;
    }
    
    // Изтриването на последния елемент работи както се очаква
    x = toDelete->data;
    delete toDelete;
    return true;
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteAfter(I const& it, T& x) {
    if (!it || it.ptr == back) {
        // Опитваме се да изтриваме след края!
        return false;
    }
    return deleteAt(it.next(), x);
}

// O(1) по време и памет
template <typename T>
bool DoubleLinkedList<T>::deleteBefore(I const& it, T& x) {
    if (it.ptr == front) {
        // опитваме се да изтриваме преди началото
        return false;
    }

    if (!it) {
        // невалиден итератор <-> искаме да изтриваме преди края
        if (front == back)
            // имаме само един елемент или нямаме елементи
            return false;
        else
            // иаме повече от един елемент
            // опитваме се да изтриваме преди края
            return deleteAt(I(back).prev(), x);
    }
    return deleteAt(it.prev(), x);
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList const& l) : front(nullptr), back(nullptr) {
    append(l);
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList const& l) {
    if (this != &l) {
        erase();
        append(l);
    }
    return *this;
}

template <typename T>
void DoubleLinkedList<T>::append(DoubleLinkedList const& l) {
    for (T const& x : l)
        insertLast(x);
}

template <typename T>
void DoubleLinkedList<T>::erase() {
    while (!empty())
        deleteFirst();
}

// O(1) по време и памет
template <typename T>
void DoubleLinkedList<T>::appendAssign(DoubleLinkedList& l) {
    if (back != nullptr)
        back->next = l.front;
    else
        front = l.front;

    if (l.front != nullptr)
        l.front->prev = back;

    if (l.back != nullptr)
        back = l.back;

    l.front = l.back = nullptr;
}

#endif
