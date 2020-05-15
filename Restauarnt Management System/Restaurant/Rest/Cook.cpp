#include "Cook.h"
#include <cstdlib>
#include <time.h>

Cook::Cook()
{
	order_counter = 0;
}

void Cook::set_max_orders(int a)
{
	max_orders = a;
}
void Cook::Assign_Order(Order* p, int ts)
{
	pOrd = p;
	order_counter++;
	free = false;
	if (order_counter == max_orders)
	{
		reset_order_counter();
		In_break = false;
		startbreak = p->getFinishTime();
		Finished_break_time = startbreak + BreakDuration;
	}
	else
		cooking_order = true;
}
void  Cook::Check_Injury(Order* pOrd,int TS)
{
	InjSpeed = speed / 2;
	int FinishedDishes = (TS - pOrd->getArrivalTime() + pOrd->getwaitingtime()) * speed; // how many dishes finished before Injury
	int SRVT_Before = FinishedDishes / speed;                      // time taken in these dishes before injury
	int SRVT_After = (pOrd->GetSize() - FinishedDishes) / InjSpeed;// the time that will be taken in the ramain dishes but with the Injury speed
	pOrd->setservicetime(SRVT_Before+SRVT_After);
}
void Cook::incrementorders()
{
	if (order_counter != max_orders)
	{
		order_counter++;
		free = false;
	}
}
bool Cook::IS_Free()
{
	return free;
}

void Cook::start_Break(int TS)
{
	free = false;
	if (order_counter == max_orders)
	{
		reset_order_counter();
		startbreak = TS + speed;
		Finished_break_time = TS + GetBreakDuration() + speed;
	}
}

void Cook::set_free()
{
	free = true;
}

void Cook::reset_order_counter()
{
	order_counter = 0;
}

bool Cook::Is_Available(int TS)
{
	if (TS >= startbreak && TS <= Finished_break_time)
	{
		return false;
	}
	else if (free == true)
	{
		return true;
	}
	return false;
}



int Cook::Get_Finish_break_time()
{
	return Finished_break_time;
}

int Cook::Get_order_counter()
{
	return order_counter;
}
int Cook::getmax_orders()
{
	return max_orders;
}

Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}

int Cook::GetBreakDuration() const
{
	return BreakDuration;
}

void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}
void Cook::SetSpeed(int smax, int smin)
{
	speed = (rand() % (smax + 1 - smin)) + smin;
}
int Cook::GetSpeed()
{
	return speed;
}
void Cook::setBreakDuration(int bmin, int bmax)
{
	BreakDuration = (rand() % (bmax + 1 - bmin)) + bmin;
}

Order* Cook::getOrder()
{
	return pOrd;
}

bool Cook::Check_Order()
{
	return cooking_order;
}