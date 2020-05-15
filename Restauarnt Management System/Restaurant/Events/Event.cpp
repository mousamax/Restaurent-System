#include "Event.h"


Event::Event(int eTime, int ordID,ORD_TYPE otype)
{
	EventTime = eTime;
	OrderID	= ordID;
	OrdType = otype;

}

ORD_TYPE Event::GetOrderType()
{
	return OrdType;
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}


Event::~Event()
{

}

