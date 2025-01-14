# SA:MP RTC 
SA:MP (untested) Simple Real Time Clock backend implementation for making Real Clock easy with friendly API 

## Installation
...

## Usage
Refer to [example](example.pwn) usage

### API

#### RTC_Init(...)
This can be used in various ways:
* `RTC_Init(customTextDraw); // init with custom TextDraw text`
* `RTC_Init(10.0, 90.0); // init with local textdraw`
* `RTC_Init(7); // init with custom timezone`
* `RTC_Init(); // init with default settings`

#### RTC_SetTextDrawPos(x, y)
This can only be used when initializing the default textdraw (not local)

#### RTC_SetTextDrawSize(size)
This can only be used when initializing the default textdraw (not local)

#### RTC_Exit()
Use this everytime you exited the gamemode/filterscript (MUST!!!)

## Credits
* knryuuki - Not So Great Scripter
