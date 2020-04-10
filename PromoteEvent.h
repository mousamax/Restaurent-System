#pragma once
#include <iostream>
#include "Rest/Order.h"
#include "Events/Event.h"
#include "LinkedList.h"

class PromoteEvent :
	public Event
{
	Order* ptr;
	double Exmoney;
	int ID;
	int TimeStep;
	LinkedList<Order*> Normal_LinkedLlist;

public:

	PromoteEvent(int TS, int id, double Exmony);


	void Execute(Restaurant* pRest);
};