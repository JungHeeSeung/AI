#include "GusetOwnedState.h"
#include "Guest.h"

#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

GuestGlobalState* GuestGlobalState::Instance()
{
	static GuestGlobalState instance;

	return &instance;
}


void GuestGlobalState::Execute(Guest* guest)
{
	// ��å �߿�
	// 3 / 10 Ȯ���� �ؾȰ��� �鸲


	if ((RandFloat() < 0.3) &&
		guest->GetFSM()->isInState(*GoForAWalk::Instance()) )
	{
		guest->GetFSM()->ChangeState(StopBySeaside::Instance());
	}
}

bool GuestGlobalState::OnMessage(Guest* guest, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_HiHoneyImHome:
	{
		cout << "\nMessage handled by " << GetNameOfEntity(guest->ID()) << " at time: "
			<< Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(guest->ID()) <<
			": ���� ���ư��߰ڱ�";

		guest->GetFSM()->ChangeState(GoHomeAndRest::Instance());
	}

	return true;

	}//end switch

	return false;
}


//------------------------------------------------------------------------GoForAWalk

GoForAWalk * GoForAWalk::Instance()
{
	static GoForAWalk instance;

	return &instance;
}

void GoForAWalk::Enter(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": ��å�̳� �Ϸ� ������!";
}

void GoForAWalk::Execute(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": ��� �� �ѷ�����...";

	guest->IncreaseFatigue();
}

void GoForAWalk::Exit(Guest * guest)
{
}

bool GoForAWalk::OnMessage(Guest * guest, const Telegram & msg)
{
	return false;
}


//------------------------------------------------------------------------StopBySeaside

StopBySeaside * StopBySeaside::Instance()
{
	static StopBySeaside instance;

	return &instance;
}

void StopBySeaside::Enter(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": �ؾȰ� �鷯����...";
}

void StopBySeaside::Execute(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": �����ϸ� ���� �� ������?";
	guest->GetFSM()->RevertToPreviousState();
	guest->IncreaseFatigue();
}

void StopBySeaside::Exit(Guest * guest)
{
}

bool StopBySeaside::OnMessage(Guest * guest, const Telegram & msg)
{
	return false;
}


//------------------------------------------------------------------------GoHomeAndRest


GoHomeAndRest * GoHomeAndRest::Instance()
{
	static GoHomeAndRest instance;

	return &instance;
}

void GoHomeAndRest::Enter(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": ������ �� ������ ���� ���̾���...";
}

void GoHomeAndRest::Execute(Guest * guest)
{
	if (!guest->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(guest->ID()) << ": ���� �ϴ� ��...";
	}
	else
	{
		//sleep
		guest->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(guest->ID()) << ": �ڴ� ��...";
	}
		
}

void GoHomeAndRest::Exit(Guest * guest)
{
	
}

bool GoHomeAndRest::OnMessage(Guest * guest, const Telegram & msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_StewReady:

		cout << "\nMessage handled by " << GetNameOfEntity(guest->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(guest->ID())
			<< ": �ų���~ ���̴�~";

		guest->GetFSM()->ChangeState(TakeAMeal::Instance());

		return true;

	}//end switch

	return false;
}

//------------------------------------------------------------------------TakeAMeal

TakeAMeal* TakeAMeal::Instance()
{
	static TakeAMeal instance;

	return &instance;
}


void TakeAMeal::Enter(Guest* guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "���� ���� ���׿�!";
}

void TakeAMeal::Execute(Guest* guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "���ֳ׿�!";

	guest->GetFSM()->ChangeState(GoForAWalk::Instance());
}

void TakeAMeal::Exit(Guest* guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "�� �Ծ����ϴ�";
}


bool TakeAMeal::OnMessage(Guest* guest, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}