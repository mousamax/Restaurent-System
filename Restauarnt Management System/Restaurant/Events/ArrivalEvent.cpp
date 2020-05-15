#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, int SIZE, int Money) :Event(eTime, oID,oType)
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
	pOrd->SetSize(Size);
	pOrd->setTotalMoney(OrdMoney);
	pOrd->setStatus(WAIT);

	pRest->Addto_Waiting_Queue(pOrd);
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2

	pRest->AddtoDemoQueue(pOrd);
}
