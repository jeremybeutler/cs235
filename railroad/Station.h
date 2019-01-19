#ifndef STATION_H
#define STATION_H

#include "Vector.h"
#include "Queue.h"
#include "Stack.h"

template<typename T>
class Station
{
private:
	Vector<T> train;
	Stack<T> stack;
	Queue<T> queue;
	T turnTableCar;
	bool empty;
	std::string temp;

public:
	Station() : train(), stack(), queue(), turnTableCar(NULL), empty(false) {}
	~Station() {}

	//void setTable(T& value) { turnTableCar = value; }
	std::string addCar(const T& value)
	{
		if (turnTableCar == NULL)
		{
			turnTableCar = value;
			return " OK";
		}
		else { return " Turntable Occuppied!"; }
		
	}

	std::string removeCar()
	{
		if (turnTableCar == NULL)	{ return " Turntable empty!"; }
		else { train.push_back(turnTableCar); turnTableCar = NULL; return " OK"; }
	}

	std::string topCar()
	{
		if (turnTableCar != NULL) { return turnTableCar; }
		else { return " Turntable empty!"; }
	}

	std::string addStack()
	{
		if (turnTableCar != NULL)
		{
			temp = stack.push(turnTableCar);
			turnTableCar = NULL;
			return " OK";
		}
		else { return " Turntable empty!"; }
		
	}
	//std::string addStack() { return stack.push(turnTableCar); }

	std::string removeStack()
	{
		if (stack.size() != 0)
		{
			turnTableCar = stack.top();
			stack.pop();
			return " OK";
		}
		else { return " Stack empty!"; }
	}

	std::string topStack()
	{
		if (stack.size() != 0) { return std::to_string(stack.top()); }
		else { return " Stack empty!"; }
	}

	std::string sizeStack() { return std::to_string(stack.size()); }

	std::string addQueue()
	{
		if (turnTableCar != NULL)
		{
			temp = queue.push(turnTableCar);
			turnTableCar = NULL;
			return " OK";
		}
		else { return " Turntable empty!"; }
		
	}
	//std::string addQueue() { return queue.push(turnTableCar); }

	std::string removeQueue()
	{
		if (queue.size() != 0)
		{
			turnTableCar = queue.top();
			queue.pop();
			return " OK";
		}
		else { return " Queue empty!"; }
	}

	std::string topQueue()
	{
		if (queue.size() != 0) { return std::to_string(queue.top()); }
		else { return " Queue empty!"; }
	}

	std::string sizeQueue()
	{
		//char* temp;
		//queue.size();
		return std::to_string(queue.size());
	}

	std::string find(T) {}

	std::string toString() const { return train.toString(); }
};


#endif