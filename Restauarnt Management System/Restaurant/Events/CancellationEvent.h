#pragma once
#include <iostream>
#include "..\Events\Event.h"
#include "..\Rest\Restaurant.h"
#include "..\Generic_DS\NewLinkedList.h"


class CancellationEvent : public Event
{
	//info about the order ralted to cancellation event
	Order* ptr;
	int TimeStep;
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	                
	int ID;
	NewLinkedList<Order*> Normal_LinkedLlist;
	
public:
	CancellationEvent(int, int);

	virtual void Execute(Restaurant* pRest);	//override execute function

};
