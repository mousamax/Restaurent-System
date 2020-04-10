#include "CancellationEvent.h"
#include "Rest/Restaurant.h"


CancellationEvent::CancellationEvent(int TS, int id) : Event(TimeStep, ID)
{
	ID = id;
	TimeStep = TS;
}

void CancellationEvent::Execute(Restaurant* pRest)  
{
	if (OrdType != TYPE_NRM)
		return;

	 Normal_LinkedLlist = pRest->GetNormalOrdersList();
	 Normal_LinkedLlist.DeleteNode(Normal_LinkedLlist.Get_Order_ByID(ID));
		 
}
