#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
//#include "Cook.h"
//#include "Generic_DS\LinkedList.h" 

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_TYPE cooktype;		//order type: Normal, vegan, VIP

	ORD_STATUS status;	//waiting, in-service, done
	//int Distance;	//The distance (in meters) between the order location and the resturant 

	int totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times

	void calcFinishTime();
	//
	// TODO: Add More Data Members As Needed
	bool IsPromoted;
	int waitingtime = 0;
	int ordersize; //numberofdishes

	//LinkedList<Order*> Normal_LinkedLlist;

	//
	int  Cook_id;
	bool urgent;
	int incrementingtime;
	int VIP_WT;
public:
	Order(int ID, ORD_TYPE r_Type);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	ORD_TYPE GetCookType() const;

	void setCookType(ORD_TYPE cook);

	void SetCookID(int d);
	int GetCookID() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;


	int getArrivalTime();
	//
	// TODO: Add More Member Functions As Needed
	void Set_IsPromoted(bool);
	bool Get_IsPromoted();
	//
	void setarrivaltime(int time);
	int  getarrivaltime();

	void setservicetime(int time);
	int  getservicetime();

	void setwaitingtime(int time);
	int  getwaitingtime();

	int calcpriority();

	void SetSize(int size);
	int  GetSize();


	int getFinishTime();

	void  setTotalMoney(int money);
	double getTotalMoney();

	void Become_Urgent();

	void Increment_Orders();

	int Get_Incrementing_Orders();

	bool Is_Urgent(int VIP_WT,int TS);
};

#endif