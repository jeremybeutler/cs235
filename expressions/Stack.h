#ifndef MY_STACK_H_
#define MY_STACK_H_
#include <vector>

template <typename T>
class Stack
{
private:
	std::vector<T> myStack;
public:
	/** Construct an empty stack */
	Stack() {}
	/** Push item on stack */
	void push(const T& item) { myStack.push_back(item); }
	/** Return top of stack */
	T& top() { return myStack.back(); }
	/** Pop top of stack */
	void pop() { myStack.pop_back(); }
	/** Return TRUE if stack is empty */
	bool empty() const { return myStack.size() == 0; }
	/** Return number of stack entries */
	size_t size() const { myStack.size(); }
};
#endif // MY_STACK_H_
