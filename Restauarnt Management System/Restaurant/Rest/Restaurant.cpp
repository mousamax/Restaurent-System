#include <cstdlib>
#include <time.h>
#include <iostream>


#include "Restaurant.h"
#include "..\Events\PromoteEvent.h"
#include "..\Events\CancellationEvent.h"

//using namespace std;

Restaurant::Restaurant()
{
	pGUI = NULL;
	//num_waiting = 0;
}
void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		interactive = true;
		dynamic_mode();
		//Interactive();
		break;
	case MODE_STEP:
		stepBystep = true;
		dynamic_mode();
		//Step_By_Step();
		break;
	case MODE_SLNT:
		silent = true;
		dynamic_mode();
		//Silent();
		break;
	case MODE_DEMO:
		Just_A_Demo();
	};
}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;
		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}

void Restaurant::AutoEvents(int CurrentTimeStep)
{
	Change_To_Autopromotion();
	Event* pE;
	while (AutoPromotionQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;
		pE->Execute(this);
		AutoPromotionQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	pCook_NRM.PrintCooks(pGUI);
	pCook_VIP.PrintCooks(pGUI);
	pCook_Veg.PrintCooks(pGUI);

	Order* pOrd;
	// 
	Normal_LinkedLlist_Waiting.PrintOrders(pGUI);
	//
	Normal_LinkedLlist_InService.PrintOrders(pGUI);
	//
	Normal_LinkedLlist_Finished.PrintOrders(pGUI);
	//
	int c = 0;
	//Order** Arr = VIP_Waiting_Queue.toArray(c);
	if (VIP_Waiting_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(VIP_Waiting_Queue.toArray(c)[i]);
		}
	}
	if (Vegan_Waiting_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(Vegan_Waiting_Queue.toArray(c)[i]);
		}
	}
	if (VIP_InService_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(VIP_InService_Queue.toArray(c)[i]);
		}
	}
	if (VIP_Finished_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(VIP_Finished_Queue.toArray(c)[i]);
		}
	}
	if (Vegan_Finished_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(Vegan_Finished_Queue.toArray(c)[i]);
		}
	}
	if (Vegan_InService_Queue.toArray(c))
	{
		for (int i = 0; i < c; i++)
		{
			pGUI->AddToDrawingList(Vegan_InService_Queue.toArray(c)[i]);
		}
	}
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
}
//// 
void Restaurant::ChangeNormalOrdersListWaiting(int id)
{
	//return Normal_LinkedLlist_Waiting;
	if (Normal_LinkedLlist_Waiting.Get_Order_ByID(id))
	{
		Normal_LinkedLlist_Waiting.DeleteNode(Normal_LinkedLlist_Waiting.Get_Order_ByID(id));
		Total_Orders--;
	}

}

NewLinkedList<Order*>& Restaurant::GetNormalOrdersListWaiting()
{
	return Normal_LinkedLlist_Waiting;
}



NewLinkedList<Order*> Restaurant::GetNormalOrdersListFinished()
{
	return Normal_LinkedLlist_Finished;
}

NewLinkedList<Order*> Restaurant::GetNormalOrdersListInService()
{
	return Normal_LinkedLlist_InService;
}


void Restaurant::Fileloading()
{
	string s;
	pGUI->PrintMessage("Please Enter filename to Load From ... ");
	filename = pGUI->GetString().c_str();	//get user input as a string 

	File.open(filename + ".txt");
	if (File.fail())
	{
		pGUI->PrintMessage("ERROR This File Doesn't Exist .... Click To Try Again ");
		pGUI->waitForClick();
		///////    Call The Function 
		Fileloading();
	}
	else
	{
		File >> s;
		Num_NormCook = atoi(s.c_str());
		File >> s;
		Num_VegCook = atoi(s.c_str());
		File >> s;
		Num_VipCook = atoi(s.c_str());
		///// Second Line /////
		File >> s;
		SN_min = atoi(s.c_str());
		File >> s;
		SN_max = atoi(s.c_str());
		File >> s;
		SG_min = atoi(s.c_str());
		File >> s;
		SG_max = atoi(s.c_str());
		File >> s;
		SV_min = atoi(s.c_str());
		File >> s;
		SV_max = atoi(s.c_str());
		///// 3rd Line /////
		File >> s;
		BO = atoi(s.c_str());
		File >> s;
		BN_min = atoi(s.c_str());
		File >> s;
		BN_max = atoi(s.c_str());
		File >> s;
		BG_min = atoi(s.c_str());
		File >> s;
		BG_max = atoi(s.c_str());
		File >> s;
		BV_min = atoi(s.c_str());
		File >> s;
		BV_max = atoi(s.c_str());
		///// Injured Prob /////////
		File >> s;
		Injprob = atof(s.c_str());
		File >> s;
		Rst = atoi(s.c_str());
		///// 5th ///////
		File >> s;
		AutoP = atof(s.c_str());
		File >> s;
		VIP_WT = atoi(s.c_str());
		///// 6th ///////
		File >> s;

		///// 7th ///////
		while (File >> s)
		{
			if (s == "R")
			{

				File >> s;
				if (s == "N")
				{
					File >> s;
					int n1 = atoi(s.c_str());
					File >> s;
					int n2 = atoi(s.c_str());
					File >> s;
					int n3 = atoi(s.c_str());
					File >> s;
					double n4 = atoi(s.c_str());
					ArrivalEvent* pArr = new ArrivalEvent(n1, n2, TYPE_NRM, n3, n4);
					EventsQueue.enqueue(pArr);
					//ArrEventsQueue.enqueue(pArr);
					//ArrEventTS.enqueue(n1);
					Total_Orders++;
				}
				else if (s == "G")
				{
					File >> s;
					int n1 = atoi(s.c_str());
					File >> s;
					int n2 = atoi(s.c_str());
					File >> s;
					int n3 = atoi(s.c_str());
					File >> s;
					double n4 = atoi(s.c_str());
					ArrivalEvent* pArr = new ArrivalEvent(n1, n2, TYPE_VGAN, n3, n4);
					EventsQueue.enqueue(pArr);
					//ArrEvent_VEG_TS.enqueue(n1);
					Total_Orders++;
				}
				else if (s == "V")
				{
					File >> s;
					int n1 = atoi(s.c_str());
					File >> s;
					int n2 = atoi(s.c_str());
					File >> s;
					int n3 = atoi(s.c_str());
					File >> s;
					double n4 = atoi(s.c_str());
					ArrivalEvent* pArr = new ArrivalEvent(n1, n2, TYPE_VIP, n3, n4);
					EventsQueue.enqueue(pArr);
					//FinishEvent_VIP_TS.enqueue(n1);
					Total_Orders++;
				}
			}
			else if (s == "X")
			{
				File >> s;
				int n1 = atoi(s.c_str());
				File >> s;
				int n2 = atoi(s.c_str());
				CancellationEvent* pCanc = new CancellationEvent(n1, n2);
				EventsQueue.enqueue(pCanc);
				//Total_Orders--;
			}
			else if (s == "P")
			{
				File >> s;
				int n1 = atoi(s.c_str());
				File >> s;
				int n2 = atoi(s.c_str());
				File >> s;
				double n3 = atoi(s.c_str());
				PromoteEvent* rPromote = new PromoteEvent(n1, n2, n3);
				EventsQueue.enqueue(rPromote);
			}
		}
		pGUI->PrintMessage("Click To Continue ... Mousa");
		pGUI->waitForClick();

	}
	File.close();
}
void Restaurant::Cooks_data()
{
	for (int i = 1; i <= Num_NormCook; i++)
	{
		Cook* ptr1 = new Cook();
		ptr1->setID(i);
		ptr1->set_max_orders(BO);
		ptr1->setType(TYPE_NRM);
		ptr1->setBreakDuration(BN_min, BN_max);
		ptr1->SetSpeed(SN_max, SN_min);
		pCook_NRM.InsertEnd(ptr1);
	}

	// VIP
	for (int i = Num_NormCook + 1; i <= Num_VipCook + Num_NormCook; i++)
	{
		Cook* ptr2 = new Cook();
		ptr2->setID(i);
		ptr2->set_max_orders(BO);
		ptr2->setType(TYPE_VIP);
		ptr2->setBreakDuration(BV_min, BV_max);
		ptr2->SetSpeed(SV_max, SV_min);
		pCook_VIP.InsertEnd(ptr2);
	}
	// Vegan
	for (int i = Num_VipCook + Num_NormCook + 1; i <= Num_VegCook + Num_VipCook + Num_NormCook; i++)
	{
		Cook* ptr3 = new Cook();
		ptr3->setID(i);
		ptr3->set_max_orders(BO);
		ptr3->setType(TYPE_VGAN);
		ptr3->setBreakDuration(BG_min, BG_max);
		ptr3->SetSpeed(SG_max, SG_min);
		pCook_Veg.InsertEnd(ptr3);
	}
}
void Restaurant::dynamic_mode()
{
	Fileloading();
	// Create File To Save Data
	oFile.open("Output_File.txt");
	oFile << "FT  ID  AT  WT  ST \n";
	//Event* pArr;
	int Finish_TS;
	Order* pOrd;
	Cook* pCook;
	int SRVTS;
	// Arr 
	int count = 0;
	Order** pOrdARR;
	Total_Num_Cooks = Num_VegCook + Num_VipCook + Num_NormCook;
	//Now We have filled EventsQueue
	CurrentTimeStep = 1;

	Cooks_data();

	//as long as events queue is not empty yet
	while (Total_Finished_Orders < Total_Orders)  //!EventsQueue.isEmpty())
	{
		int time = CurrentTimeStep;
		int cooks = Total_Num_Cooks;
		string co = "  Number of Cooks: ";
		msg = "TS: " + to_string(time) + co + to_string(cooks) + "  Number of Total Orders: " + to_string(Total_Orders) + "   NRM: " + to_string(Num_NRM_WAITING) + "   VIP: " + to_string(Num_VIP_WAITING) + "   VEG: " + to_string(Num_VEG_WAITING) + "    Finished: " + to_string(Total_Finished_Orders);
		pGUI->PrintMessage(msg);
		//The next line may add new orders to the DEMO_Queue
		AutoEvents(CurrentTimeStep);
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		pGUI->PrintMessage(msg);
		/////////////////////////////////////////////////////////////////////////////////////////
		//// Move From In Service To Finished
		while (Normal_LinkedLlist_InService.get_firstitem())//FinishEvent_NRM_TS.peekFront(Finish_TS))
		{
			pOrd = Normal_LinkedLlist_InService.get_firstitem()->getItem();
			if (pOrd->getFinishTime() < CurrentTimeStep)//Finish_TS == CurrentTimeStep)
			{

				// OutPut File Data
				pOrd = Normal_LinkedLlist_InService.get_firstitem()->getItem();
				oFile << to_string(CurrentTimeStep) + "   " + to_string(pOrd->GetID()) + "   " + to_string(pOrd->getArrivalTime()) + "   " + to_string(pOrd->getservicetime() - pOrd->getArrivalTime()) + "   " + to_string(CurrentTimeStep - pOrd->getservicetime()) + "\n";
				Sum_WT += pOrd->getservicetime() - pOrd->getArrivalTime();
				Sum_ST += CurrentTimeStep - pOrd->getservicetime();
				//
				pOrd->setStatus(DONE);
				Normal_LinkedLlist_Finished.InsertEnd(pOrd);
				Normal_LinkedLlist_InService.DeleteFirst();
				// Free Cook
				pCook = pCook_NRM.Get_Cook_ByID(pOrd->GetCookID());
				if (pCook)
				{
					pCook_NRM.DeleteNode(pCook);
					pCook_NRM.InsertBeg(pCook);
					pCook->set_free();
				}
				else if (pCook_VIP.Get_Cook_ByID(pOrd->GetCookID()))
				{
					pCook = pCook_VIP.Get_Cook_ByID(pOrd->GetCookID());
					pCook_VIP.DeleteNode(pCook);
					pCook_VIP.InsertBeg(pCook);
					pCook->set_free();
				}
				// 
				Total_Finished_Orders++;
			}
			else
			{
				break;
			}
		}
		//while (VIP_InService_Queue.peekFront(pOrd))//FinishEvent_VIP_TS.peekFront(Finish_TS))
		//{
		pOrdARR = VIP_InService_Queue.toArray(count);
		for (int i = 0; i < count; i++)
		{
			if (pOrdARR[i]->getFinishTime() < CurrentTimeStep)
			{
				VIP_InService_Queue.dequeue(pOrdARR[i]);

				pOrdARR[i]->setStatus(DONE);
				//
				oFile << to_string(CurrentTimeStep) + "   " + to_string(pOrdARR[i]->GetID()) + "   " + to_string(pOrdARR[i]->getArrivalTime()) + "   " + to_string(pOrdARR[i]->getservicetime() - pOrdARR[i]->getArrivalTime()) + "   " + to_string(CurrentTimeStep - pOrdARR[i]->getservicetime()) + "\n";
				Sum_WT += pOrdARR[i]->getservicetime() - pOrdARR[i]->getArrivalTime();
				Sum_ST += CurrentTimeStep - pOrdARR[i]->getservicetime();
				//
				VIP_Finished_Queue.enqueue(pOrdARR[i]);
				// Move Cook
				pCook = pCook_VIP.Get_Cook_ByID(pOrdARR[i]->GetCookID());
				if (pCook != nullptr)
				{
					pCook_VIP.DeleteNode(pCook);
					pCook_VIP.InsertBeg(pCook);
					pCook->set_free();
				}
				else if (pCook_NRM.Get_Cook_ByID(pOrdARR[i]->GetCookID()) != nullptr)
				{
					pCook = pCook_NRM.Get_Cook_ByID(pOrdARR[i]->GetCookID());

					pCook_NRM.DeleteNode(pCook);
					pCook_NRM.InsertBeg(pCook);
					pCook->set_free();
				}
				else if (pCook_Veg.Get_Cook_ByID(pOrdARR[i]->GetCookID()) != nullptr)
				{
					pCook = pCook_Veg.Get_Cook_ByID(pOrdARR[i]->GetCookID());
					pCook_Veg.DeleteNode(pCook);
					pCook_Veg.InsertBeg(pCook);
					pCook->set_free();
				}
				FinishEvent_VIP_TS.dequeue(Finish_TS);
				Total_Finished_Orders++;
			}
		}
		//}								
		//
		while (Vegan_InService_Queue.peekFront(pOrd))//FinishEvent_VEG_TS.peekFront(Finish_TS))
		{
			if (pOrd->getFinishTime() < CurrentTimeStep)
			{
				Vegan_InService_Queue.dequeue(pOrd);
				pOrd->setStatus(DONE);
				//
				oFile << to_string(CurrentTimeStep) + "   " + to_string(pOrd->GetID()) + "   " + to_string(pOrd->getArrivalTime()) + "   " + to_string(pOrd->getservicetime() - pOrd->getArrivalTime()) + "   " + to_string(CurrentTimeStep - pOrd->getservicetime()) + "\n";
				Sum_WT += pOrd->getservicetime() - pOrd->getArrivalTime();
				Sum_ST += CurrentTimeStep - pOrd->getservicetime();
				//
				Vegan_Finished_Queue.enqueue(pOrd);
				//
				pCook = pCook_Veg.Get_Cook_ByID(pOrd->GetCookID());
				pCook_Veg.DeleteNode(pCook);
				pCook_Veg.InsertBeg(pCook);
				pCook->set_free();
				// 
				//FinishEvent_VEG_TS.dequeue(Finish_TS);
				Total_Finished_Orders++;
			}
			else
			{
				break;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		/// From Wait To Service
		while (VIP_Waiting_Queue.peekFront(pOrd))
		{
			bool Not_SRV = true;
			if (pCook_VIP.get_firstitem() != NULL)
			{
				pCook = pCook_VIP.get_firstitem()->getItem();
				if (pOrd->Is_Urgent(VIP_WT, CurrentTimeStep) && pCook->IS_Free())
				{
					VIP_Waiting_Queue.dequeue(pOrd);
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_VIP.DeleteFirst();
					pCook_VIP.InsertEnd(pCook);

					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
				else if (pCook->Is_Available(CurrentTimeStep))
				{
					VIP_Waiting_Queue.dequeue(pOrd);
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_VIP.DeleteFirst();
					pCook_VIP.InsertEnd(pCook);

					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
			}
			if (Not_SRV && pCook_NRM.get_firstitem() != NULL)
			{
				pCook = pCook_NRM.get_firstitem()->getItem();
				if (pOrd->Is_Urgent(VIP_WT, CurrentTimeStep) && pCook->IS_Free())
				{
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_NRM.DeleteFirst();
					pCook_NRM.InsertEnd(pCook);
					
					VIP_Waiting_Queue.dequeue(pOrd);
					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
				else if (pCook->Is_Available(CurrentTimeStep))
				{
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_NRM.DeleteFirst();
					pCook_NRM.InsertEnd(pCook);
					
					VIP_Waiting_Queue.dequeue(pOrd);
					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
			}
			if (Not_SRV && pCook_Veg.get_firstitem() != NULL)
			{
				pCook = pCook_Veg.get_firstitem()->getItem();
				if (pOrd->Is_Urgent(VIP_WT, CurrentTimeStep) && pCook->IS_Free())
				{
					pCook = pCook_Veg.get_firstitem()->getItem();
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_Veg.DeleteFirst();
					pCook_Veg.InsertEnd(pCook);
					
					VIP_Waiting_Queue.dequeue(pOrd);
					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
				else if (pCook->Is_Available(CurrentTimeStep))
				{
					pCook = pCook_Veg.get_firstitem()->getItem();
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					Not_SRV = false;
					pCook_Veg.DeleteFirst();
					pCook_Veg.InsertEnd(pCook);
					
					VIP_Waiting_Queue.dequeue(pOrd);
					VIP_InService_Queue.enqueue(pOrd);
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());

				}
			}
			if(Not_SRV)
			{
				break;
			}
		}
		// Move Vegan From Waiting To in-Service
		while (Vegan_Waiting_Queue.peekFront(pOrd))
		{
			pCook = pCook_Veg.get_firstitem()->getItem();
			if (pCook->Is_Available(CurrentTimeStep))
			{
				pOrd->SetCookID(pCook->GetID());
				pOrd->setStatus(SRV);
				SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
				pOrd->setservicetime(SRVTS);
				pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
				//
				pCook->Assign_Order(pOrd, CurrentTimeStep);
				pCook_Veg.DeleteFirst();
				pCook_Veg.InsertEnd(pCook);
				
				Vegan_InService_Queue.enqueue(pOrd);
				Vegan_Waiting_Queue.dequeue(pOrd);
				// Order Finish Time
				FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
			}
			else
			{
				break;
			}
		}
		// Move Normal Order From Waiting To In-service
		while (Normal_LinkedLlist_Waiting.get_firstitem())
		{
			pOrd = Normal_LinkedLlist_Waiting.get_firstitem()->getItem();
			if (pCook_NRM.get_firstitem())
			{
				pCook = pCook_NRM.get_firstitem()->getItem();
				if (pCook->Is_Available(CurrentTimeStep))
				{
					pOrd = Normal_LinkedLlist_Waiting.get_firstitem()->getItem();
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					pCook_NRM.DeleteFirst();
					pCook_NRM.InsertEnd(pCook);
					
					Normal_LinkedLlist_InService.InsertEnd(pOrd);
					Normal_LinkedLlist_Waiting.DeleteFirst();
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
				else if (pCook_VIP.get_firstitem() != NULL && pCook_VIP.get_firstitem()->getItem()->Is_Available(CurrentTimeStep))
				{
					pCook = pCook_VIP.get_firstitem()->getItem();
					pOrd = Normal_LinkedLlist_Waiting.get_firstitem()->getItem();
					pOrd->SetCookID(pCook->GetID());
					pOrd->setStatus(SRV);
					SRVTS = ((pOrd->GetSize() / (float)pCook->GetSpeed()));
					pOrd->setservicetime(SRVTS);
					pOrd->setwaitingtime(CurrentTimeStep - pOrd->getArrivalTime());
					//
					pCook->Assign_Order(pOrd, CurrentTimeStep);
					pCook_VIP.InsertEnd(pCook);
					pCook_VIP.DeleteFirst();
					
					Normal_LinkedLlist_InService.InsertEnd(pOrd);
					Normal_LinkedLlist_Waiting.DeleteFirst();
					// Order Finish Time
					FinishEvent_NRM_TS.enqueue(CurrentTimeStep + pCook->GetSpeed());
				}
				else
				{
					break;
				}
			}
			else
				break;
		}
		//////////////////////////
		if (interactive)
		{
			FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->PrintMessage(msg);
			pGUI->waitForClick();
		}
		else if (stepBystep)
		{
			FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->PrintMessage(msg);
			Sleep(1000);
		}
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}
	outputFile();
}
void Restaurant::Check_Injury(Order* pOrd)
{
	Cook* pCook;
	Order* pOrdV;
	Order* pOrdG;
	Order* pOrdN;
	int VT = -1, GT = -1, NT = -1;
	if (rand() <= Injprob)
	{
		if (Vegan_InService_Queue.peekFront(pOrdG))
		{
			GT = pOrdG->getArrivalTime() + pOrdG->getwaitingtime();
		}
		if (VIP_InService_Queue.peekFront(pOrdV))
		{
			VT = pOrdV->getArrivalTime() + pOrdV->getwaitingtime();
		}
		if (Normal_LinkedLlist_InService.get_firstitem())
		{
			pOrdN = Normal_LinkedLlist_InService.get_firstitem()->getItem();
			NT = pOrdN->getArrivalTime() + pOrdN->getwaitingtime();
		}
		if (GT != -1 && GT >= VT && GT >= NT)
		{
			pCook = pCook_Veg.Get_Cook_ByID(pOrdG->GetCookID());
			pCook->Check_Injury(pOrdG, CurrentTimeStep);
		}
		else if (NT != -1 && NT >= GT && NT >= VT)
		{
			pCook = pCook_NRM.Get_Cook_ByID(pOrdN->GetCookID());
			pCook->Check_Injury(pOrdN, CurrentTimeStep);
		}
		else if (VT != -1)
		{
			pCook = pCook_VIP.Get_Cook_ByID(pOrdV->GetCookID());
			pCook->Check_Injury(pOrdV, CurrentTimeStep);
		}
	}
}
void Restaurant::outputFile()
{
	float avgWT = Sum_WT / (float)(Num_NRM_WAITING + Num_VEG_WAITING + Num_VIP_WAITING);
	float avgST = Sum_ST / (float)(Num_NRM_WAITING + Num_VEG_WAITING + Num_VIP_WAITING);
	oFile << "\n";
	oFile << "------- # Statistics # -------- \n";
	oFile << "Orders: " + to_string(Total_Orders) + " [Norm: " + to_string(Num_NRM_WAITING) + ", Veg: " + to_string(Num_VEG_WAITING) + ", VIP: " + to_string(Num_VIP_WAITING) + " ] \n";
	oFile << "cooks:  " + to_string(Total_Num_Cooks) + " [Norm: " + to_string(Num_NormCook) + " , Veg: " + to_string(Num_VegCook) + " , VIP: " + to_string(Num_VipCook) + " ] \n";
	oFile << "Avg Wait = " + to_string(avgWT) + ", Avg Serv = " + to_string(avgST) + " \n";
	oFile << "Auto - promoted: 7 \n";

	oFile.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2

	int EventCnt;
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;
	Cook* pC = new Cook[C_count];
	int cID = 1;



	for (int i = 0; i < C_count; i++)
	{
		cID += (rand() % 15 + 1);
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand() % TYPE_CNT));
	}


	int EvTime = 0;

	int O_id = 1;

	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for (int i = 0; i < EventCnt; i++)
	{
		O_id += (rand() % 4 + 1);
		int OType = rand() % TYPE_CNT;	//Randomize order type		
		EvTime += (rand() % 5 + 1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime, O_id, TYPE_VIP, 3, 2);//wrong
		EventsQueue.enqueue(pEv);
	}

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file





	//Now We have filled EventsQueue (randomly)
	CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step


/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for (int i = 0; i < C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);

		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		//Sleep(1000);
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete[]pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();



}
////////////////

void Restaurant::AddtoDemoQueue(Order* pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

void Restaurant::Addto_Waiting_Queue(Order* pOrd)
{
	if (pOrd->GetType() == TYPE_VIP)
	{
		Total_Orders++;
		VIP_Waiting_Queue.enqueue(pOrd);
		Num_VIP_WAITING++;
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		Normal_LinkedLlist_Waiting.InsertEnd(pOrd);
		Num_NRM_WAITING++;
	}
	else if (pOrd->GetType() == TYPE_VGAN)
	{
		Vegan_Waiting_Queue.enqueue(pOrd);
		Num_VEG_WAITING++;
	}
	pGUI->PrintMessage(msg);
}

void Restaurant::Addto_InService_Queue(Order* pOrd)
{
	//num_waiting--;
	if (pOrd->GetType() == TYPE_VIP)
	{
		VIP_InService_Queue.enqueue(pOrd);
		Num_VIP_WAITING--;
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		Normal_LinkedLlist_InService.InsertEnd(pOrd);
		Num_NRM_WAITING--;
	}
	else if (pOrd->GetType() == TYPE_VGAN)
	{
		Vegan_InService_Queue.enqueue(pOrd);
		Num_VEG_WAITING--;
	}
}

void Restaurant::Addto_Finished_Queue(Order* pOrd)
{
	Total_Finished_Orders++;
	if (pOrd->GetType() == TYPE_VIP)
	{
		VIP_Finished_Queue.enqueue(pOrd);
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		Normal_LinkedLlist_Finished.InsertEnd(pOrd);
		Num_NRM_WAITING--;
	}
	else if (pOrd->GetType() == TYPE_VGAN)
	{
		Vegan_Finished_Queue.enqueue(pOrd);
	}
}

void Restaurant::Change_To_Autopromotion()
{
	Node<Order*>* ptr = Normal_LinkedLlist_Waiting.get_firstitem();
	while (ptr != NULL && ptr->getItem() != NULL)
	{
		if (ptr->getItem()->getArrivalTime() + AutoP == CurrentTimeStep)
		{
			PromoteEvent* rPromote = new PromoteEvent(CurrentTimeStep, ptr->getItem()->GetID(), 0);
			AutoPromotionQueue.enqueue(rPromote);
			Event* pE;
		}
		ptr = ptr->getNext();
	}
}

/*void Restaurant::Change_To_Urgent()
{
	Order** ptr = VIP_Waiting_Queue.toArray(Num_VIP_WAITING);
	int i = 0;
	bool check = false;
	for (i = 0;i < Num_VIP_WAITING;i++)
	{
		if (ptr[i]->getArrivalTime() + VIP_WT == CurrentTimeStep)
		{
			ptr[i]->Become_Urgent();
			check = true;
		}

	}
	if (check == true)
	{
		Order* p;
		VIP_Waiting_Queue.dequeue(p);
		while (VIP_Waiting_Queue.dequeue(p))
		{

		}
		for (i = 0;i < Num_VIP_WAITING;i++)
		{
			Addto_Waiting_Queue(ptr[i]);
		}
	}
}*/

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////