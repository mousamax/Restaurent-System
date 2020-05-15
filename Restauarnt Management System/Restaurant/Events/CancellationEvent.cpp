#include "CancellationEvent.h"


CancellationEvent::CancellationEvent(int TS, int id) : Event(TS, id, TYPE_NRM)
{
	ID = id;
	TimeStep = TS;
	
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	//if ( OrdType == TYPE_NRM)
	pRest->ChangeNormalOrdersListWaiting(ID);

		//Normal_LinkedLlist = pRest->GetNormalOrdersListWaiting();
		//if(Normal_LinkedLlist.Get_Order_ByID(ID)->GetType()==TYPE_NRM)
		//int x = Normal_LinkedLlist.getFirstItem()->getItem()->GetID();
		/*if(Normal_LinkedLlist.Get_Order_ByID(ID))
		{ 
			Normal_LinkedLlist.DeleteNode(Normal_LinkedLlist.Get_Order_ByID(ID));
		}
		*/
		

		//ID msh mawgood
	
}
