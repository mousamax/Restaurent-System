#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "..\PromoteEvent.h"
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"

Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
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


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	for(int i = 0;i<Num_NormCook;i++)
	{
		pGUI->AddToDrawingList(&pCook_NRM[i]);
	}
	for(int i = 0;i<Num_VipCook;i++)
	{
		pGUI->AddToDrawingList(&pCook_VIP[i]);
	}
	for(int i = 0;i<Num_VegCook;i++)
	{
		pGUI->AddToDrawingList(&pCook_Veg[i]);
	}
	//  Change ........
	/*for(int i = 0;i<Num_NormCook;i++)
	{
	pGUI->AddToDrawingList(pOrd);
	}*/

	
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	
}
//// 
LinkedList<Order*> Restaurant::GetNormalOrdersList()
{
	return Normal_LinkedLlist;
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
		SN = atoi(s.c_str());
		File >> s;
		SG = atoi(s.c_str());
		File >> s;
		SV = atoi(s.c_str());
		///// 3rd Line /////
		File >> s;
		BO = atoi(s.c_str());
		File >> s;
		BN = atoi(s.c_str());
		File >> s;
		BG = atoi(s.c_str());
		File >> s;
		BV = atoi(s.c_str());
		///// 4th ///////
		File >> s;
		AutoP = atoi(s.c_str());
		///// 5th ///////
		File >> s;
		///// 6th ///////
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
		pGUI->PrintMessage(s);
		pGUI->waitForClick();

	}
	File.close();
}
void Restaurant::Interactive()
{
	Fileloading();
	//Now We have filled EventsQueue
	int CurrentTimeStep = 1;


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
		if(CurrentTimeStep % 5 == 0)
		{
			Order* pOrd;
			VIP_InService_Queue.dequeue(pOrd);
			VIP_Finished_Queue.enqueue(pOrd);

			Vegan_InService_Queue.dequeue(pOrd);
			Vegan_Finished_Queue.enqueue(pOrd);
			
		}
		/////////////////////////////////////////////////////////////////////////////////////////
		FillDrawingList();

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}
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
		pEv = new ArrivalEvent(EvTime, O_id, TYPE_VIP,3,2);//wrong
		EventsQueue.enqueue(pEv);
	}

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file





	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;


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
		Sleep(1000);
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
		VIP_Waiting_Queue.enqueue(pOrd);
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		//Normal_LinkedLlist.InsertEnd(pOrd);
	}
	else
	{
		Vegan_Waiting_Queue.enqueue(pOrd);
	}
}

void Restaurant::Addto_InService_Queue(Order* pOrd)
{
	if (pOrd->GetType() == TYPE_VIP)
	{
		VIP_InService_Queue.enqueue(pOrd);
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		//Normal_LinkedLlist.InsertEnd(pOrd);
	}
	else
	{
		Vegan_InService_Queue.enqueue(pOrd);
	}
}

void Restaurant::Addto_Finished_Queue(Order* pOrd)
{
	if (pOrd->GetType() == TYPE_VIP)
	{
		VIP_Finished_Queue.enqueue(pOrd);
	}
	else if (pOrd->GetType() == TYPE_NRM)
	{
		//Normal_LinkedLlist.InsertEnd(pOrd);
	}
	else
	{
		Vegan_Finished_Queue.enqueue(pOrd);
	}
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////