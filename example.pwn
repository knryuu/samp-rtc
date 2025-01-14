
#include <open.mp>
#include <RealTimeClock>

main() {}

new Text:CustomClockText;

public OnGameModeInit()
{
	CustomClockText = TextDrawCreate(...);
	RTC_Init(CustomClockText);
	return 1;
}

public OnGameModeExit()
{
	RTC_Exit();
	return 1;
}

public OnPlayerConnect(playerid)
{
	TextDrawShowForPlayer(playerid, CustomClockText);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	TextDrawHideForPlayer(playerid, CustomClockText);
	return 1;
}
