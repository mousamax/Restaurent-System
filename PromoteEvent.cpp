#include "PromoteEvent.h"
#include"..\Rest\Restaurant.h"


PromoteEvent::PromoteEvent(int TS, int id, double Exmony = 0) : Event(TS, id)
{
	Exmoney = Exmony;
	TimeStep = TS;
	ID = id;
}


void PromoteEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(ptr->GetID(), TYPE_VIP);
	Order* pOldOrd;
	pOldOrd = pRest->GetNormalOrdersListWaiting().Get_Order_ByID(ID);
	if (Exmoney > 0)
	{
		pOrd->setTotalMoney(pOldOrd->getTotalMoney() + Exmoney);
	}
	else
	{
		pOrd->setTotalMoney(pOldOrd->getTotalMoney());
	}
	//  
	pOrd->setarrivaltime(pOldOrd->getArrivalTime());
	pOrd->setordersize(pOldOrd->getordersize());
	pOrd->setservicetime(pOldOrd->getservicetime());
	pOrd->setStatus(pOldOrd->getStatus());
	pOrd->setwaitingtime(pOldOrd->getwaitingtime());
	pOrd->Set_IsPromoted(true);
	pRest->Addto_Waiting_Queue(pOrd);
	// Delete Old Order
	//Normal_LinkedLlist = pRest->GetNormalOrdersList();
	//Normal_LinkedLlist.DeleteNode(Normal_LinkedLlist.Get_Order_ByID(ID));


	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phases 1&2
	pRest->AddtoDemoQueue(pOrd);
}