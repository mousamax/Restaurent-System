#pragma once
#include"NewNode.h"
#include "..\Rest\Order.h"

template<class T>
class PriorityQueueOrders
{
		NewNode<T>* head;
		NewNode<T>* tail;
		int orderscount;
	public:
		PriorityQueueOrders()
		{
			head = nullptr;
			tail = nullptr;
			orderscount = 0;
		}
		~PriorityQueueOrders()
		{
			clear();
		}
		void clear()
		{
			NewNode<T>* tmp = head;
			while (tmp->getnext() != nullptr)
			{
				NewNode<T>* tmp2 = tmp;
				tmp = tmp->getnext();
				delete tmp2;
			}
		}


		void dequeue()
		{
			T val = head->getitem();
			NewNode<T>* del = head;
			head = head->getnext();
			delete del;
			--orderscount;
			if (empty())
			{
				tail = nullptr;
			}
		}

		bool empty()
		{
			return(head == nullptr);
		}

		void enqueue(T neworder)
		{
			NewNode<T>* insertorder = NewNode<T>(neworder);
			if (empty() || head->getpriority() < insertorder->getpriority())
			{
				insertorder->setNext(head);
				head = insertorder;
			}
			else
			{
				NewNode<T>* tmp = head;
				while (tmp->getNext() != nullptr && tmp->getNext()->getpriority() >= insertorder->getpriority())
				{
					tmp = tmp->getNext();
				}
				insertorder->setNext(tmp->getNext());
				tmp->setNext(insertorder);
			}
		}
};