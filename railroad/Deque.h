#ifndef DEQUE_H
#define DEQUE_H
#include "DequeInterface.h"

#define DEFAULT_CAPACITY 4

template<typename T>
class Deque : public DequeInterface<T>
{
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* the_data;


	void reallocate()
	{
		size_t new_capacity = 2 * capacity;
		T* new_data = new T[new_capacity];
		size_t j = front_index + 1;
		for (size_t i = 0; i < num_items; i++)
		{
			new_data[i] = the_data[j];
			j = (j + 1) % capacity;
		}
		front_index = new_capacity - 1;
		rear_index = num_items;
		capacity = new_capacity;
		std::swap(the_data, new_data);

		delete[] new_data;
	}

public:
	Deque(void) :
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(DEFAULT_CAPACITY - 1),
		rear_index(0),
		the_data(new T[DEFAULT_CAPACITY]) {}
	~Deque(void) {}

	/** Insert item at front of deque */
	virtual void push_front(const T& value)
	{
		if (num_items == capacity)
		{
			reallocate();
		}
		num_items++;
		the_data[front_index] = value;
		front_index = (front_index - 1) % capacity;
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value)
	{
		if (num_items == capacity)
		{
			reallocate();
			//rear_index = num_items;
		}
		num_items++;
		the_data[rear_index] = value;
		rear_index = (rear_index + 1) % capacity;
	}

	/** Remove the front item of the deque */
	virtual void pop_front(void)
	{
		num_items--;
		front_index = (front_index + 1) % capacity;
		the_data[front_index] = NULL;
	}

	/** Remove the rear item of the deque */
	virtual void pop_back(void)
	{
		num_items--;
		rear_index = (rear_index - 1) % capacity;
		the_data[rear_index] = NULL;
	}

	/** Return the front item of the deque (Do not remove) */
	virtual T& front(void)
	{
		return the_data[(front_index + 1) % capacity];
	}

	/** Return the rear item of the deque (Do not remove) */
	virtual T& back(void)
	{
		return the_data[(rear_index - 1) % capacity];
	}

	/** Return the number of items in the deque */
	virtual size_t size(void) const
	{
		return num_items;
	}

	/** Return true if deque is empty */
	virtual bool empty(void) const
	{
		return num_items == 0;
	}

	/** Return item in deque at index (0 based) */
	virtual T& at(size_t i) const
	{
		if (i >= num_items)
		{
			throw i;
		}
		return the_data[(front_index + i + 1) % capacity];
	}

	/** Return the deque items */
	virtual std::string toString() const
	{
		std::stringstream out;
		for (size_t i = 0; i < num_items; i++)
		{
			out << at(i) << " ";
		}
		return out.str();
	}
};
#endif // DEQUE_H