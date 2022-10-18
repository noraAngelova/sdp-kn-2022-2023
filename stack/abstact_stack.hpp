#ifndef _ABSTRACT_STACK_HPP
#define _ABSTRACT_STACK_HPP

template <typename T>
class AbstractStack {
public:
	// проверка за празнота на стек
	virtual bool empty() const = 0;

	// включване на елемент и връща дали е било успешно
	virtual void push(T const& x) = 0;

	// изключване на елемент
	virtual T pop() = 0;

	// поглеждане на последно включения елемент
	virtual T top() const = 0;
};

#endif