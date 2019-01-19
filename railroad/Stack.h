#ifndef STACK_H
#define STACK_H

#include "Deque.h"

template<typename T>
class Stack
{
private:
	Deque<T> container;
public:
	Stack() : container() {}
	~Stack() {}

	std::string push(const T& value)
	{ 
		container.push_back(value);
		return " OK";
	}
	void pop() { container.pop_back(); }
	T& top() { return container.back(); }
	size_t size() { return container.size(); }
	T& at(size_t value) { return container.at(value); }
	std::string toString() const { return container.toString(); }
};

#endif STACK_H
 