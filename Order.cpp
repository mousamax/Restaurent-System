#include "Order.h"
#include "..\Rest\Restaurant.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	IsPromoted = false;
}

Order::~Order()
{
}

int Order::getArrivalTime()
{
	return ArrTime;
}


int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::Set_IsPromoted(bool b)
{
	IsPromoted = b;
}

bool Order::Get_IsPromoted()
{
	return IsPromoted;
}

void Order::setarrivaltime(int time)
{
	ArrTime = time;
}

int Order::getarrivaltime()
{
	return ArrTime;
}

void Order::setservicetime(int time)
{
	ServTime = time;
}

int Order::getservicetime()
{
	return ServTime;
}

void Order::setwaitingtime(int time)
{
	waitingtime = time;
}

int Order::getwaitingtime()
{
	return waitingtime;
}

void Order::calcFinishTime()
{
	FinishTime = ArrTime + waitingtime + ServTime;
}

int Order::getFinishTime()
{
	return FinishTime;
}

int Order::calcpriority()
{
	if (this->GetType() != TYPE_NRM && this->GetType() != TYPE_VGAN)
	{
		//priority equation;

	}
	else if (this->GetType() == TYPE_VGAN)
	{
		return -1;
	}
	else
	{
		return -2;
	}
}
void Order::setordersize(int s)
{
	if (s > 0)
		ordersize = s;
	else
		ordersize = 0;
}

int Order::getordersize()
{
	return ordersize;
}


void Order::setTotalMoney(double money)
{
	totalMoney = money;
}

double Order::getTotalMoney()
{
	return totalMoney;
}
