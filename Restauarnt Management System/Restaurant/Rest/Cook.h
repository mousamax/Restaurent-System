#pragma once

#include "..\Defs.h"
#include "Order.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan) ..cook type
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int BreakDuration; //each cook takes a break after serving n consecutive orders
	int max_orders; // Orders Before taking a break
	int order_counter=0;
	bool free = true;	// Check if working on order now
	int Finished_break_time;
	int startbreak;
	/// InjProb & RstPeriod
	float Injprob;
	int Rst;
	int InjSpeed;
	Order* pOrd = nullptr;
	bool cooking_order;
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	int GetBreakDuration() const;
	void setID(int);
	void setType(ORD_TYPE);

	void setBreakDuration(int bmin,int bmax);

	// Assign Order To Cook
	void Assign_Order(Order* p,int ts);
	// 
	void Check_Injury(Order* pOrd,int TS);
	// set the maximum orders for each cook
	void set_max_orders(int a);

	// return the maximum orders for each cook
	int getmax_orders();

	// here we increment the number of orders a cook has taken 
	void incrementorders();

	// return the order made until now
	int Get_order_counter();

	// here we the cook begins his break and we send the timestep at which he started his break 
	void start_Break(int TS);
	//
	bool In_break = false;
	// return the finished time for the cook's break 
	int Get_Finish_break_time();

	// make the cook available to serve // must be called
	void set_free();

	// make the order counter zero for when the cook starts his break
	void reset_order_counter();

	// Check Is this cook is available from break duration
	bool Is_Available(int TS);

	// you must call these functions:
	// set_free
	// Is Available
	// startbreak
	// increment order
	bool IS_Free();
	// 
	void SetSpeed(int,int);
	int GetSpeed();

	Order* getOrder();

	bool Check_Order();
};
