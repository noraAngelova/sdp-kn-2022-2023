#ifndef _LINKED_LIST_HPP
#define _LINKED_LIST_HPP

/*	Представяне на елемент на свързан списък с една връзка
	 ___________
	|ст/ст| адр |
	|_____|_____|
	 data   next
*/
template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement<T>* next;
};

// Декларация на клас LinkedList
template <typename T>
class LinkedList;

// Дефиниране на клас Итератор
template <typename T>
class LinkedListIterator {
	// Съкратени записи за шаблон на елемент от свързан списък и итератор
	using LLE = LinkedListElement<T>;
	using I = LinkedListIterator<T>;

	// Осигурява достъп до вътрешното представяне на списъка
	friend LinkedList<T>;

	// Реализира абстракция на позиция чрез ptr към елемент
	LLE* ptr;
public:
	// Подразбиращ се конструктор и конструктор с един параметър
	LinkedListIterator(LLE* pos = nullptr) : ptr(pos) {}

	// Метод за взимане на итератор към следващ елемент
	I next() const {
		// Проверка за валидност на текущия итератор
		if (!valid()) {
			// Запазва и връща текущия итератор
			return *this;
		}
		// Създава нов обект итератор, който се свързва със следващия елемент на списъка
		return I(ptr->next);
	}

	// Проверка за валидност (обхваща и случая с достигането на края на свързания списък)
	bool valid() const {
		return ptr != nullptr;
	}

	// Методи за извличане на стойността на елемента свързан с итератора
	T const& getConst() const {
		return ptr->data;
	}

	T& get() const {
		return ptr->data;
	}

	// Синтактична захар
	// it <=> it.valid();
	operator bool() const {
		return valid();
	}

	// ++it
	I& operator++() {
		return (*this = next());
	}

	// it++
	I operator++(int) {
		I saved = *this;
		++(*this);
		return saved;
	}

	// *it = 3;
	T& operator*() {
		return get();
	}

	// Сравнение на итератори
	// it1 == it2
	bool operator==(I const& it) const {
		return ptr == it.ptr;
	}

	// it1 != it2
	bool operator!=(I const& it) const {
		return !(*this == it);
	}

	// Преместване с n позиции
	// it += n
	I& operator+=(unsigned n) {
		for (int i = 0; i < n; ++i) {
			++(*this);
		}

		return *this;
	}
};

// Дефиниране на клас Свързан списък
template <typename T>
class LinkedList {
	using LLE = LinkedListElement<T>;

	// Представяне на свързан списък с два указателя
	LLE* front, * back;

	// Помощна член-функция за изтриване на динамично заделената памет
	void erase();
public:
	// Ще използваме I като тип за LinkedListIterator<T>
	using I = LinkedListIterator<T>;

	// Подразбиращ се конструктор, който създава празен списък
	LinkedList() : front(nullptr), back(nullptr) {}

	// Конструктор за копиране и оператор за присвояване за свързан списък
	LinkedList(LinkedList<T> const& ll);
	LinkedList<T>& operator=(LinkedList<T> const& ll);

	// Деструктор
	~LinkedList() {
		erase();
	}

	// Move конструктор и оператор за присвояване
	LinkedList(LinkedList<T>&& ll);
	LinkedList<T>& operator=(LinkedList<T>&& ll);


	// Методи за взимане на позиции в свързания списък
	// Метод за начало на свързан списък
	I begin() const {
		return I(front);
	}
	// Метод връщащ края на свързан списък
	I end() const {
		// Създава итератор от nullptr, 
		// което позволява използване на цикли до края на списъка - до невалидна позиция
		// Реализацията е сходна с stl-ската
		return I();
	}

	// Метод, който проверява дали списъкът е празен
	bool empty() const {
		return front == nullptr && back == nullptr;
	}

	// Методи за извличане на стойност на елемент
	T const& getAt(I const& it) const;
	T& getAt(I const& it);

	// Основни методи за добавяне на елемент
	bool insertBefore(I const& it, T const& x);
	bool insertAfter(I const& it, T const& x);

	// Основни методи за изтриване на елемент
	bool deleteBefore(I const& it, T& x);
	bool deleteAfter(I const& it, T& x);
	bool deleteAt(I const& it, T& x);

	// Допълнителни методи за добавяне и изтриване на елементи
	// O(1) по време и памет
	bool insertFirst(T const& x) {
		return insertBefore(begin(), x);
	}
	bool insertLast(T const& x) {
		return insertAfter(end(), x);
	}

	// Фунции за изтриване на елемент без допълнителен параметър
	bool deleteBefore(I const& it) {
		T tmp;
		return deleteBefore(it, tmp);
	}
	bool deleteAfter(I const& it) {
		T tmp;
		return deleteAfter(it, tmp);
	}
	bool deleteAt(I const& it) {
		T tmp;
		return deleteAt(it, tmp);
	}

	// O(1) по време и по памет
	bool deleteFirst(T& x) {
		return deleteAt(begin(), x);
	}

	bool deleteFirst() {
		T tmp;
		return deleteFirst(tmp);
	}

	// O(n) по време, O(1) по памет
	bool deleteLast(T& x) {
		return deleteAt(end(), x);
	}

	// O(n) по време, O(1) по памет
	bool deleteLast() {
		T x;
		return deleteLast(x);
	}

	// Методи за конкатенация на елементи от списъка подаден като параметър
	void append(LinkedList<T> const& ll);
	void appendAssign(LinkedList<T>& ll);

	// Синтактична захар
	// Добавяне на елемент чрез оператора +=
	LinkedList<T>& operator+=(T const& x) {
		insertLast(x);
		return *this;
	}

private:
	// Допълнителен метод за намиране на предходен елемент
	I findPrev(I const& it);
};

template <typename T>
void LinkedList<T>::append(LinkedList const& l) {
	for (T const& x : l)
		insertLast(x);
}

// Методът използва паметта за елементите на списъка l и го променя
template <typename T>
void LinkedList<T>::appendAssign(LinkedList& l) {
	// Проверява дали списъкът е празен
	if (back != nullptr)
		back->next = l.front;
	else
		front = l.front;

	// Проверка дали подадения като параметър списък е празен
	if (l.back != nullptr)
		back = l.back;

	// Занулява указателите, за да избегне поделянето на памет
	l.front = l.back = nullptr;
}

// Метод за изтриване на динамично заделената памет
template <typename T>
void LinkedList<T>::erase() {
	while (!empty())
		deleteFirst();
}

// O(n) по време и O(1) по памет
template <typename T>
LinkedListIterator<T> LinkedList<T>::findPrev(LinkedListIterator<T> const& it) {
	// Първи се определя кой е текущият елемент
	LLE* target;
	if (!it)
		// Ще ще търси елементът преди последния
		target = back;
	else
		target = it.ptr;

	I result = begin();
	while (result && result.ptr->next != target)
		++result;

	// result.ptr->next == target
	return result;
}

// Конструктор за копиране
template <typename T>
LinkedList<T>::LinkedList(LinkedList const& l) : front(nullptr), back(nullptr) {
	// Използва се функцията append
	// Функцията вмъква елементи със същите стойности от списъка l в списъка *this
	append(l);
}

// Оператор за присвояване
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList const& l) {
	if (this != &l) {
		erase();
		append(l);
	}
	return *this;
}


// O(1) по време и памет
template <typename T>
bool LinkedList<T>::insertAfter(I const& it, T const& x) {
	if (empty()) {
		return insertFirst(x);
	}

	LLE* newElem = new LLE{ x, nullptr };

	// it.ptr == nullptr <=> искаме да добавяме в края
	if (!it || it.ptr == back) {
		// Добавя се елемент в края
		back->next = newElem;
		back = newElem;
	}
	else {
		// Добавя се елемент някъде по средата
		newElem->next = it.ptr->next;
		it.ptr->next = newElem;
	}
	return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::insertBefore(I const& it, T const& x) {
	if (it == begin()) {
		// Вмъкваме в началото: специален случай
		LLE* newElem = new LLE{ x, front };
		front = newElem;
		// Проверка дали списъкът е празен
		if (back == nullptr)
			// вмъкваме в празен списък
			back = newElem;
		return true;
	}
	return insertAfter(findPrev(it), x);
}

// O(1) по време и по памет
template <typename T>
bool LinkedList<T>::deleteAfter(I const& it, T& x) {
	if (!it)
		// Не може да се изтрива след невалиден итератор(позиция)
		return false;

	LLE* deletedElem = it.ptr->next;

	if (!deletedElem)
		// Не може да се изтрива след края
		return false;

	it.ptr->next = deletedElem->next;
	x = deletedElem->data;

	if (back == deletedElem)
		// Изтрива се последният елемент
		back = it.ptr;

	delete deletedElem;
	return true;
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::deleteAt(I const& it, T& x) {
	if (!empty() && it == begin()) {
		x = front->data;
		LLE* deletedElem = front;
		front = front->next;
		if (back == deletedElem) {
			// Изтрива се последният елемент от списъка
			back = nullptr;
		}
		delete deletedElem;
		return true;
	}

	return deleteAfter(findPrev(it), x);
}

// O(n) по време и O(1) по памет
template <typename T>
bool LinkedList<T>::deleteBefore(I const& it, T& x) {
	if (it == begin()) {
		return false;
	}
	return deleteAt(findPrev(it), x);
}

#endif
