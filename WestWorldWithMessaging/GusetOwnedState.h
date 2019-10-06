#pragma once

//------------------------------------------------------------------------
//
//  Name:   GuestOwnedStates.h
//
//  Desc:   MinerWifeOwnedState.h를 기반으로 만듦
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Guest;

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GuestGlobalState : public State<Guest>
{
private:

	GuestGlobalState() {}

	//copy ctor and assignment should be private
	GuestGlobalState(const GuestGlobalState&);
	GuestGlobalState& operator=(const GuestGlobalState&);

public:

	//this is a singleton
	static GuestGlobalState* Instance();

	virtual void Enter(Guest* guest) {}

	virtual void Execute(Guest* guest);

	virtual void Exit(Guest* guest) {}

	virtual bool OnMessage(Guest* guest, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GoForAWalk : public State<Guest>
{
private:

	GoForAWalk() {}

	//copy ctor and assignment should be private
	GoForAWalk(const GoForAWalk&);
	GoForAWalk& operator=(const GoForAWalk&);

public:

	//this is a singleton
	static GoForAWalk* Instance();

	virtual void Enter(Guest* guest);

	virtual void Execute(Guest* guest);

	virtual void Exit(Guest* guest);

	virtual bool OnMessage(Guest* guest, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class StopBySeaside : public State<Guest>
{
private:

	StopBySeaside() {}

	//copy ctor and assignment should be private
	StopBySeaside(const StopBySeaside&);
	StopBySeaside& operator=(const StopBySeaside&);

public:

	//this is a singleton
	static StopBySeaside* Instance();

	virtual void Enter(Guest* guest);

	virtual void Execute(Guest* guest);

	virtual void Exit(Guest* guest);

	virtual bool OnMessage(Guest* guest, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GoHomeAndRest : public State<Guest>
{
private:

	GoHomeAndRest() {}

	//copy ctor and assignment should be private
	GoHomeAndRest(const GoHomeAndRest&);
	GoHomeAndRest& operator=(const GoHomeAndRest&);

public:

	//this is a singleton
	static GoHomeAndRest* Instance();

	virtual void Enter(Guest* guest);

	virtual void Execute(Guest* guest);

	virtual void Exit(Guest* guest);

	virtual bool OnMessage(Guest* guest, const Telegram& msg);

};

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class TakeAMeal : public State<Guest>
{
private:

	TakeAMeal() {}

	//copy ctor and assignment should be private
	TakeAMeal(const TakeAMeal&);
	TakeAMeal& operator=(const TakeAMeal&);

public:

	//this is a singleton
	static TakeAMeal* Instance();

	virtual void Enter(Guest* guest);

	virtual void Execute(Guest* guest);

	virtual void Exit(Guest* guest);

	virtual bool OnMessage(Guest* guest, const Telegram& msg);
};