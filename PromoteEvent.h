#pragma once
#include <iostream>
#include "Rest/Order.h"
#include "Events/Event.h"
template<class T>
class PromoteEvent :
	public Event
{
	Order* ptr;
	double Exmoney;
	int ID;
	int TS;

public:

	PromoteEvent(int id, int TS, double Exmony);


	void Execute(Restaurant* pRest);
};
