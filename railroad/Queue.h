#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template<typename T>
class Queue
{
private:
	Deque<T> container;
public:
	Queue() : container() {}
	~Queue() {}

	std::string push(const T& value)
	{
		container.push_back(value);
		return " OK";
	}
	void pop()	{ container.pop_front(); }
	T& top() { return container.front(); }
	size_t size() const { return container.size(); }
	T& at(size_t i)
	{
		try
		{
			return container.at(i);
		}
		catch (T bad_index)
		{
			std::cout << "Invalid index: " << bad_index;
		}
	}
	std::string toString() const { return container.toString(); }
};


#endif QUEUE_H
