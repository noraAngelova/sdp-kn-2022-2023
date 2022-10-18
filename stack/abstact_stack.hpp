#ifndef _ABSTRACT_STACK_HPP
#define _ABSTRACT_STACK_HPP

template <typename T>
class AbstractStack {
public:
	// �������� �� �������� �� ����
	virtual bool empty() const = 0;

	// ��������� �� ������� � ����� ���� � ���� �������
	virtual void push(T const& x) = 0;

	// ���������� �� �������
	virtual T pop() = 0;

	// ���������� �� �������� ��������� �������
	virtual T top() const = 0;
};

#endif