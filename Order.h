#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
//#include "Generic_DS\LinkedList.h" 

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	//int Distance;	//The distance (in meters) between the order location and the resturant 

	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times


	//
	// TODO: Add More Data Members As Needed
	bool IsPromoted;
	int waitingtime;
	int ordersize; //numberofdishes
	//LinkedList<Order*> Normal_LinkedLlist;

	//

public:
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	//void SetDistance(int d);
	//int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;


	int getArrivalTime();
	//
	// TODO: Add More Member Functions As Needed
	void Set_IsPromoted(bool);
	bool Get_IsPromoted();
	//
	void setarrivaltime(int time);
	int getarrivaltime();
	void setservicetime(int time);
	int getservicetime();
	void setwaitingtime(int time);
	int getwaitingtime();
	int calcpriority();
	void setordersize(int size);
	int getordersize();
	void calcFinishTime();

	int getFinishTime();

	void setTotalMoney(double money);
	double getTotalMoney();
};

#endif