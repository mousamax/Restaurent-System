#pragma once
#include"NewNode.h"


template<class T>
class PriorityQueueOrders
{
		NewNode<T>* frontPtr;
		NewNode<T>* backPtr;
		int orderscount;
	public:
		PriorityQueueOrders()
		{
			frontPtr= nullptr;
			backPtr = nullptr;
			orderscount = 0;
		}
		~PriorityQueueOrders()
		{
			clear();
		}
		void clear()
		{
			NewNode<T>* tmp = frontPtr;
			while (tmp->getNext() != nullptr)
			{
				NewNode<T>* tmp2 = tmp;
				tmp = tmp->getNext();
				delete tmp2;
			}
		}


		bool dequeue(T& frntEntry)
		{
			if (isEmpty())
				return false;

			NewNode<T>* nodeToDeletePtr = frontPtr;
			frntEntry = frontPtr->getitem();
			frontPtr = frontPtr->getNext();
			// Queue is not empty; remove front
			if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
				backPtr = nullptr;

			// Free memory reserved by the dequeued node
			delete nodeToDeletePtr;


			return true;

		}

		void enqueue(T neworder)
		{
			NewNode<T>* insertorder = new NewNode<T>(neworder);
			if (isEmpty() || frontPtr->getpriority() < insertorder->getpriority())
			{
				insertorder->setNext(frontPtr);
				frontPtr = insertorder;
			}
			else
			{
				NewNode<T>* tmp = frontPtr;
				while (tmp->getNext() != nullptr && tmp->getNext()->getpriority() >= insertorder->getpriority())
				{
					tmp = tmp->getNext();
				}
				insertorder->setNext(tmp->getNext());
				tmp->setNext(insertorder);
			}
		}

		bool isEmpty() const
		{
			if (frontPtr == nullptr)
				return true;
			else
				return false;
		}

		T* toArray(int& count)
		{
			count = 0;

			if (!frontPtr)
				return nullptr;
			//counting the no. of items in the Queue
			NewNode<T>* p = frontPtr;
			while (p)
			{
				count++;
				p = p->getNext();
			}


			T* Arr = new T[count];
			p = frontPtr;
			for (int i = 0; i < count;i++)
			{
				Arr[i] = p->getitem();
				p = p->getNext();
			}
			return Arr;
		}

		bool peekFront(T& frntEntry) const
		{
			if (isEmpty())
				return false;

			frntEntry = frontPtr->getitem();
			return true;

		}
};