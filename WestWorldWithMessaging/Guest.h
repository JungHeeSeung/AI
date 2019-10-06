#pragma once

//------------------------------------------------------------------------
//
//  Name: MinersWife.h
//
//  Desc: MinersWife.h 를 복사한 후, 수정함
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "GusetOwnedState.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

class Guest : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Guest>* m_pStateMachine;

	location_type   m_Location;

	// 피곤한 정도
	int                   m_iFatigue;

public:
	Guest(int id) :m_Location(shack),
					m_iFatigue(0),
					BaseGameEntity(id)

	{
		//set up the state machine
		m_pStateMachine = new StateMachine<Guest>(this);

		m_pStateMachine->SetCurrentState(GoForAWalk::Instance());

		m_pStateMachine->SetGlobalState(GuestGlobalState::Instance());
	}

	~Guest() { delete m_pStateMachine; }

	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Guest>* GetFSM()const { return m_pStateMachine; }

	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

};
