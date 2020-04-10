#pragma once
#include"Defs.h"
#include "Rest/Order.h"
template <class T>
class NewNode
{
private:
	Order item; // A data item
	NewNode<T>* next; // Pointer to next node
	int priority;
public:
	NewNode();
	NewNode(const T& r_Item);	//passing by const ref.
	NewNode(const T& r_Item, NewNode<T>* nextNodePtr);
	Order setitem(const Order& r_Item);
	void setNext(NewNode<T>* nextNodePtr);
	Order getitem() const;
	NewNode<T>* getNext() const;
	int getpriority();
}; // end Node

template < typename T>
NewNode<T>::NewNode()
{
	next = nullptr;
}

template < typename T>
NewNode<T>::NewNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
NewNode<T>::NewNode(const T& r_Item, NewNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
Order NewNode<T>::setitem(const Order& r_Item)
{
	item = r_Item;
}

template < typename T>
void NewNode<T>::setNext(NewNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
Order NewNode<T>::getitem() const
{
	return item;
}

template < typename T>
NewNode<T>* NewNode<T>::getNext() const
{
	return next;
}

template<typename T>
int NewNode<T>::getpriority()
{
	return item.calcpriority();
};
