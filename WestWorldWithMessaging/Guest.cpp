#include "Guest.h"

bool Guest::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Guest::Update()
{
	//set text color to blue
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Guest::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}