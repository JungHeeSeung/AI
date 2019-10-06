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
	// 산책 중에
	// 3 / 10 확률로 해안가에 들림


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
			": 슬슬 돌아가야겠군";

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
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": 산책이나 하러 가볼까!";
}

void GoForAWalk::Execute(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": 어딜 더 둘러볼까...";

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
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": 해안가 들러볼까...";
}

void StopBySeaside::Execute(Guest * guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": 낚시하면 좋을 것 같은데?";
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
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": 이쪽이 그 집으로 가는 길이었나...";
}

void GoHomeAndRest::Execute(Guest * guest)
{
	if (!guest->Fatigued())
	{
		cout << "\n" << GetNameOfEntity(guest->ID()) << ": 게임 하는 중...";
	}
	else
	{
		//sleep
		guest->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(guest->ID()) << ": 자는 중...";
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
			<< ": 신난다~ 밥이다~";

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
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "음식 냄새 좋네요!";
}

void TakeAMeal::Execute(Guest* guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "맛있네용!";

	guest->GetFSM()->ChangeState(GoForAWalk::Instance());
}

void TakeAMeal::Exit(Guest* guest)
{
	cout << "\n" << GetNameOfEntity(guest->ID()) << ": " << "잘 먹었습니다";
}


bool TakeAMeal::OnMessage(Guest* guest, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}