#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int SIZE, double Money) :Event(eTime, oID)
{
	OrdType = oType;
	Size = SIZE;
	OrdMoney = Money;
	TimeStep = eTime;

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order* pOrd = new Order(OrderID, OrdType);
	pOrd->setarrivaltime(TimeStep);
	pOrd->setordersize(Size);
	pOrd->setTotalMoney(OrdMoney);

	pRest->Addto_InService_Queue(pOrd);
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2

	pRest->AddtoDemoQueue(pOrd);

}
