#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_


//#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h" 
#include "..\Events\Event.h"
//#include "Order.h"
#include "..\Generic_DS\NewLinkedList.h" 
#include "..\Events\ArrivalEvent.h"
#include"..\Generic_DS\PriorityQueue.h"

//////////////////////////////
#include<fstream>

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	    //Queue of all events that will be loaded from file
	Queue<Event*> AutoPromotionQueue;
	Queue<Event*> ArrEventsQueue;  //Queue of all ARR events that will be loaded from file
	Queue<int> ArrEventTS;
	Queue<int> FinishEvent_NRM_TS;
	Queue<int> FinishEvent_VIP_TS;
	Queue<int> FinishEvent_VEG_TS;

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>

	PriorityQueueOrders<Order*> VIP_Waiting_Queue;
	NewLinkedList<Order*> Normal_LinkedLlist_Waiting;
	Queue<Order*> Vegan_Waiting_Queue;
	//
	PriorityQueueOrders<Order*> VIP_InService_Queue;
	NewLinkedList<Order*>Normal_LinkedLlist_InService;
	Queue<Order*> Vegan_InService_Queue;
	//
	PriorityQueueOrders<Order*> VIP_Finished_Queue;
	NewLinkedList<Order*> Normal_LinkedLlist_Finished;
	Queue<Order*> Vegan_Finished_Queue;
	//
	
	// TODO: Add More Data Members As Needed
	ifstream File;
	string filename;
	// To Make Output File
	ofstream oFile;
	// ==== First Line ==== ///
	int Num_VipCook;
	int Num_NormCook;
	int Num_VegCook;
	int Total_Num_Cooks;
	NewLinkedList<Cook*> pCook_VIP;
	NewLinkedList<Cook*> pCook_NRM;
	NewLinkedList<Cook*> pCook_Veg;
	/*Cook* pCook_VIP;
	Cook* pCook_NRM;
	Cook* pCook_Veg;*/
	// ============ Second Line ---> S = Speed , N = Normal .....
	int SN_max, SN_min, SG_max, SG_min,SV_max,SV_min;
	// ============ 3rd line ------> BO ->the number of orders a cook must prepare before taking a break
	// B -> The break duration For Each Type
	int BO, BN_max,BN_min,  BG_max,BG_min    ,BV_max, BV_min;
	//  represent the number of timesteps after which an order is automatically promoted to VIP. 
	int AutoP;
	int VIP_WT;
	/// InjProb & RstPeriod
	float Injprob;
	int Rst;
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
	// Number Of Waiting Orders
	//int num_waiting;
	int Total_Finished_Orders = 0;
	int Total_Orders = 0;
	int Num_NRM_WAITING = 0;
	int Num_VIP_WAITING = 0;
	int Num_VEG_WAITING = 0;
	int Sum_WT = 0;
	int Sum_ST = 0;
	string msg;					// Status Bar Massege
	bool interactive = false;	// for dynamic mode
	bool silent = false;		// for dynamic mode
	bool stepBystep = false;	// for dynamic mode
	bool Cancelled = false;
	int CurrentTimeStep;
public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();




	void FillDrawingList();
	//
	void Cooks_data();
	// TODO: Add More Member Functions As Needed
	// Check_Injury
	void Check_Injury(Order * pOrd);
	void Fileloading();
	// Output File Function
	void outputFile();
	//
	void Interactive();
	//
	void Step_By_Step();
	//
	void Silent();
	//
	void dynamic_mode();

/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	//void AddtoVIPQueue(Order* po);
	//void AddtoNormalQueue(Order* po);
	void Addto_Waiting_Queue(Order* po);
	void Addto_InService_Queue(Order* po);
	void Addto_Finished_Queue(Order* po);
	/// ================================================================================================== 
	void ChangeNormalOrdersListWaiting(int id);
	NewLinkedList<Order*>& GetNormalOrdersListWaiting();
	NewLinkedList<Order*> GetNormalOrdersListInService();		  
    NewLinkedList<Order*>GetNormalOrdersListFinished();
	void Change_To_Autopromotion();
	void AutoEvents(int CurrentTimeStep);
	void Change_To_Urgent();
};

#endif