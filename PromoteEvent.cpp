#include "PromoteEvent.h"
#include"Rest/Restaurant.h"

template<class T>
PromoteEvent<T>::PromoteEvent(int id, int ts, double Exmony = 0) : Event(TS, id)
{
	Exmoney = Exmony;
	ID = id;
	TS = ts;
}

template<class T>
void PromoteEvent<T>::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(ptr->GetID(), TYPE_VIP);
	if (Exmoney > 0)
	{
		pOrd->setTotalMoney(pOrd->getTotalMoney() + Exmoney);

		pRest->Normal_LinkedLlist()->

	}
	else
	{

	}
	pRest->AddtoQueue(pOrd);
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2

	pRest->AddtoDemoQueue(pOrd);
}