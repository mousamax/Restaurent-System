#pragma once
#include <iostream>
#include "Rest/Order.h"
#include "Events/Event.h"
#include "LinkedList.h"


class CancellationEvent : public Event
{
	//info about the order ralted to cancellation event
	Order* ptr;
	int TimeStep;
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	                
	int ID;
	LinkedList<Order*> Normal_LinkedLlist;
public:
	CancellationEvent(int TS, int id);

	virtual void Execute(Restaurant* pRest);	//override execute function

};