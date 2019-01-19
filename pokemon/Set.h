//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef SET_H
#define SET_H
#include <string>
#include "BST.h"

template<typename T>
class Set
{
private:
	BST<T> bst;
public:
	Set() : bst() {}
	~Set() { clear(); }

	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
		         pair.second = true if successfully inserted, else false. */
	//virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item) 
	{
		return bst.addNode(item);
	}

	/** Removes all items from the set. */
	virtual void clear() 
	{
		bst.clearTree();
	}

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const 
	{
		return bst.size();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item) 
	{
		return (bst.find(item)) ? 1 : 0;
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString()
	{
		return bst.toString();
	}

	// extraction operator friended with toString() method
	friend std::ostream& operator<< (std::ostream& os, Set& set)
	{
		os << set.toString();
		return os;
	}
};
#endif // SET_H