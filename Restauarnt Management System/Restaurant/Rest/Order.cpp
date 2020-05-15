#include "Order.h"
//#include "..\Rest\Restaurant.h"

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	IsPromoted = false;
	urgent = false;
	incrementingtime = 0;
}

Order::~Order()
{
}

ORD_TYPE Order::GetCookType() const
{
	return cooktype;
}

void Order::setCookType(ORD_TYPE cook)
{
	cooktype = cook;
}
void Order::SetCookID(int id)
{
	Cook_id = id;
}
int Order::GetCookID() const
{
	return Cook_id;
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
	calcFinishTime();
	return FinishTime;
}

int Order::calcpriority()
{
	int p = 0;
	if (this->GetType() != TYPE_NRM && this->GetType() != TYPE_VGAN)
	{
		p = (((this->getTotalMoney() / this->GetSize()) * this->getTotalMoney()) + (100 / this->getArrivalTime())) / 10;
		return p;
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
void Order::SetSize(int s)
{
	if (s > 0)
		ordersize = s;
	else
		ordersize = 0;
}

int Order::GetSize()
{
	return ordersize;
}


void Order::setTotalMoney(int money)
{
	totalMoney = money;
}

double Order::getTotalMoney()
{
	return totalMoney;
}

void Order::Become_Urgent()
{
	urgent = true;

}

void Order::Increment_Orders()
{
	incrementingtime++;

}

int Order::Get_Incrementing_Orders()
{
	return incrementingtime;
}

bool Order::Is_Urgent(int VIP_WT,int TS)
{
	if (ArrTime + VIP_WT <= TS)
	{
		return true;
	}
	return false;
}