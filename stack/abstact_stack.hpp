#ifndef _ABSTRACT_STACK_HPP
#define _ABSTRACT_STACK_HPP

template <typename T>
class AbstractStack {
public:
	// проверка за празнота на стек
	virtual bool empty() const = 0;

	// Включване на елемент и връща дали е било успешно
	virtual void push(T const& x) = 0;

	// Изключване на елемент
	virtual void pop() = 0;

	// поглеждане на последно включения елемент
	virtual T top() const = 0;
};

#endif
