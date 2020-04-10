#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_


#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h" 
#include "..\Events\Event.h"
#include "Order.h"

//////////////////////////////
#include<fstream>

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>

	Queue<Order*> VIP_Waiting_Queue;
	//LinkedList<Order*> Normal_LinkedLlist;
	Queue<Order*> Vegan_Waiting_Queue;
	//
	Queue<Order*> VIP_InService_Queue;
	//LinkedList<Order*> Normal_LinkedLlist;
	Queue<Order*> Vegan_InService_Queue;
	//
	Queue<Order*> VIP_Finished_Queue;
	//LinkedList<Order*> Normal_LinkedLlist;
	Queue<Order*> Vegan_Finished_Queue;
	//
	
	// TODO: Add More Data Members As Needed
	ifstream File;
	string filename;
	// ==== First Line ==== ///
	int Num_VipCook;
	int Num_NormCook;
	int Num_VegCook;
	Cook* pCook_VIP;
	Cook* pCook_NRM;
	Cook* pCook_Veg;
	// ============ Second Line ---> S = Speed , N = Normal .....
	int SN, SG, SV;
	// ============ 3rd line ------> BO ->the number of orders a cook must prepare before taking a break
	// B -> The break duration For Each Type
	int BO, BN, BG, BV;
	//  represent the number of timesteps after which an order is automatically promoted to VIP. 
	int AutoP;
	//  represents the number of events 
	int M;

	//Events:
	//Arrival event  Denoted By Letter ----> R
	// event timestep. (order arrival time)
	int Arrival_TS;
	// orderID
	int Arrival_ID;
	// the number of dishes of the order
	int Arrival_SIZE;
	// the total order money
	int Arrival_MONY;

	//Cancelation event Denoted By Letter ---->  X
	// event timestep. 
	int Cancel_TS;
	// orderID
	int Cancel_ID;

	//Promotion event line
	// event timestep. (order arrival time)
	int Promotion_TS;
	// orderID
	int Promotion_ID;
	// the total order Extra money
	int ExMONY;

public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();




	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	void Fileloading();

	void Interactive();
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	//void AddtoVIPQueue(Order* po);
	//void AddtoNormalQueue(Order* po);
	void Addto_Waiting_Queue(Order* po);
	void Addto_InService_Queue(Order* po);
	void Addto_Finished_Queue(Order* po);
	/// ================================================================================================== 
	LinkedList<Order*> GetNormalOrdersList();
};

#endif