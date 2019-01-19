#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"

template<typename T>
class Vector
{
private:
	Deque<T> container;
public:
	Vector() : container() {}
	~Vector() {}

	void push_back(const T& value)
	{
		container.push_back(value);
	}

	void pop_back()
	{
		container.pop_back();
	}

	T& back()
	{
		return container.back();
	}

	size_t size() const
	{
		return container.size();
	}

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

#endif VECTOR_H