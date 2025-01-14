/*
 * @Title: SA:MP Real Time Clock
 * @Version: 0.0.1-a
 *
 * Copyright (C) 2025  Yuuki X
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
 
#tryinclude <open.mp>

#if !defined _INC_open_mp
    #include <a_samp>

    #if !defined IsValidTimer
        static stock IsValidTimer(timer) { return (timer != 0); } // monkey patch for omp
    #endif
#endif

static
    Text:RTC_SavedTextDraw = INVALID_TEXT_DRAW,
    RTC_HeartBeatTimer = 0,
    RTC_LocalTimeZone = cellmin,
    bool:RTC_IsTextDrawLocal = bool:-1;

stock bool:RTC_Init(Text:textdraw = INVALID_TEXT_DRAW, timezone = cellmin)
{
    if (IsValidTextDraw(RTC_SavedTextDraw))
    {
        print("RTC ERROR: RealTimeClock already initialized!");
        return false;
    }

    if (!IsValidTextDraw(textdraw))
    {
        #if !defined RTC_DISABLE_SECONDS
        RTC_SavedTextDraw = TextDrawCreate(0.0, 0.0, "00:00:00");
        #else
        RTC_SavedTextDraw = TextDrawCreate(0.0, 0.0, "00:00");
        #endif

        TextDrawFont(RTC_SavedTextDraw, 1);
        TextDrawColor(RTC_SavedTextDraw, 0xFFFFFFFF);
        RTC_IsTextDrawLocal = true;
        print("RTC LOG: Using default Local RTC TextDraw!");
    }
    else
    {
        RTC_SavedTextDraw = textdraw;
        RTC_IsTextDrawLocal = false;
        print("RTC LOG: Loaded the textdraw into the internal variable");
    }

    if (-12 <= timezone <= 12)
    {
        RTC_LocalTimeZone = timezone;
    }

    RTC_HeartBeatTimer = SetTimer(#RTC_HeartBeat, 1000, true);
    print("RTC LOG: RTC Initialized");
    return true;
}

stock bool:RTC_SetTextDrawPos(Float:x, Float:y)
{
    if (RTC_IsTextDrawLocal == false)
    {
        return false;
    }
    TextDrawSetPos(RTC_SavedTextDraw, x, y);
    return true;
}

stock bool:RTC_SetTextDrawSize(size)
{
    if (RTC_IsTextDrawLocal == false)
    {
        return false;
    }
    TextDrawTextSize(RTC_SavedTextDraw, size);
    return true;
}

stock RTC_Exit()
{
    if (IsValidTimer(RTC_HeartBeatTimer))
    {
        KillTimer(RTC_HeartBeatTimer);
        RTC_HeartBeatTimer = 0;
    }

    if (IsValidTextDraw(RTC_SavedTextDraw))
    {
        if (RTC_IsTextDrawLocal == true)
        {
            RTC_SavedTextDraw = INVALID_TEXT_DRAW; // detach
        }
        else
        {
            TextDrawDestroy(RTC_SavedTextDraw); // destroy
        }
    }

    RTC_LocalTimeZone = cellmin;
    RTC_IsTextDrawLocal = bool:-1; // reset to unknown state
}

forward RTC_HeartBeat();
public RTC_HeartBeat()
{
    #if !defined RTC_DISABLE_SECONDS
    new hour, minute, second;
    gettime(hour, minute, second);
    #else
    new hour, minute;
    gettime(hour, minute);
    #endif

    if (RTC_LocalTimeZone != cellmin)
    {
        // Fixing time
        hour = (hour + RTC_LocalTimeZone) % 24;
    }

    new textDrawFormat;
    #if !defined RTC_DISABLE_SECONDS
    format(textDrawFormat, sizeof(textDrawFormat), "%02d:%02d:%02d", hour, minute, second);
    #else
    format(textDrawFormat, sizeof(textDrawFormat), "%02d:%02d", hour, minute);
    #endif
    TextDrawSetString(RTC_SavedTextDraw, textDrawFormat);
    return 1;
}

