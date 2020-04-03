#include <iostream>
#include"Generic_DS/Node.h"
using namespace std;


template <typename T>
class LinkedList
{
private:
	Node<T>* Head;//Pointer to the head of the list
	Node<T>* Tail;
	int count;
public:
	Node<T>* gethead()
	{
		return Head;
	}

	//returns the count of the number of elements in the nodes.
	int getcount()
	{
		return count;
	}

	LinkedList()
	{
		Head = nullptr;
	}


	//Function: PrintList.
	//prints the values of all nodes in a linked list.
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}

	// InsertBeg.
	// Creates a new node and adds it to the beginning of a linked list
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;
	}

	// Function: DeleteAll.
	//Deletes all nodes of the list.
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}


	//InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data){
		if (Head==nullptr) {
			Head=new Node<T>(data);
			return;
		}
		
		Node<T> *ptr=Head;

		while(ptr->getNext()!=NULL)
			ptr=ptr->getNext();

		Node<T>* ptr2=new Node<T>(data);
		ptr->setNext(ptr2);
	}

	//Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key)
	{
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == Key)
			{
				return true;
			}
			p = p->getNext();
		}
		return false;
	}

	//CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count1 = 0;
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == value)
			{
				count1++;
			}
			p = p->getNext();
		}
		return count;
	}

	//Delete Node 
	//Delete the first Node with value equal to the data sent 
	//Deletes only one node 
	//if not found, returns false
	bool DeleteNode(const T& value)
	{
		Node<T>* p = Head;
		Node<T>* temp = NULL;
		while (p)
		{
			if (p->getNext() != NULL)
				if (p->getNext()->getNext() == NULL)
				{
					if (p->getItem() == value)
					{
						temp = p;
						Head = p->getNext();
						delete temp;
						return true;
					}
					else if (p->getNext()->getItem() == value)
					{
						temp = p->getNext();
						p->setNext(p->getNext()->getNext());
						delete temp;
						return true;
					}
				}
			if (p->getNext() != NULL)
				if ((p->getNext())->getItem() == value)
				{
					if (p->getNext()->getNext() == NULL)
					{
						temp = p->getNext();
						p->setNext(NULL);
						delete temp;
						return true;
					}
					temp = p->getNext();
					p->setNext(p->getNext()->getNext());
					delete temp;
					return true;
				}

			if (p->getItem() == value)
			{
				temp = p;
				Head = Head->getNext();;
				delete temp;
				return true;
			}
			else
			{
				if (p == NULL)
					return false;
			}

			p = p->getNext();
		}

		return false;
	}

	//DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* temp = Head;
		Head = Head->getNext();
		delete temp;
	}


	// DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* p = Head;
		while (p->getNext()->getNext())
		{
			p = p->getNext();
		}
		Node<T>* ptr = p->getNext();
		p->setNext(NULL);

	}
	

	//DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* p = Head;
		Node<T>* p2 = Head->getNext();
		Node<T>* temp;
		int c = 0;
		if (p2)
		{
			while (p->getItem() == value)
			{
				temp = p;
				Head = Head->getNext();
				p = Head;
				if (p)
				{
					p2 = Head->getNext();
					delete temp;
				}
				else
				{
					p2 = NULL;
					break;
				}
				c++;
			}
		}
		else
		{
			if (p->getItem() == value)
			{
				temp = p;
				Head = Head->getNext();
				c++;
				delete temp;
				return true;
			}
		}

		while (p2)
		{
			if (p2->getItem() == value)
			{
				temp = p2;
				p2 = p2->getNext();
				p->setNext(p2);
				delete temp;
				c++;
			}
			else
			{
				p = p->getNext();
				p2 = p2->getNext();
			}
		}
	}

	//Reverse
	//this would reverse the whole linkedlist
	void Reverse()
	{
		Node<T>* p = NULL;
		Node<T>* c = Head;
		Node<T>* n;
		while (c)
		{
			n = c->getNext();
			c->setNext(p);
			p = c;
			c = n;
		}
		Head = p;
	}

	//GetPointerTo
	//This gets the pointer(Node) that points to the value sent in the parameter list. 
	Node<T>* GetPointerTo(const T& it)
	{
		bool found = false;
		Node<T>* p = Head;
		while (!found && p != NULL)
		{
			if (p->getItem() == it)
			{
				found = true;
			}
			else
			{
				p = p->getNext();
			}
		}
		return p;
	}

	//frequency
	//returns the number of times a value was repeated in the list.
	int frequency(const T& it)
	{
		int freq = 0;
		Node<T>* p = Head;
		while (p)
		{
			if (p->getItem() == it)
			{
				freq++;
			}
			p = p->getNext();
		}
		return freq;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
};
