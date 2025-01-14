# SA:MP RTC 
SA:MP (untested) Simple Real Time Clock backend implementation for making Real Clock easy with friendly API 

## Installation
...

## Usage
Refer to [example](example.pwn) usage

### API

#### RTC_Init(...)
This can be used in various ways:
* `RTC_Init(.textdraw = customTextDrawVariable); // init with custom TextDraw text`
* `RTC_Init(.timzeone = 7); // init with custom timezone`
* `RTC_Init(); // init with default settings`

#### RTC_SetTextDrawPos(x, y)
This can only be used when initializing the default settings

#### RTC_SetTextDrawSize(size)
This can only be used when initializing the default settings

#### RTC_Exit()
Use this everytime you exited the gamemode/filterscript (MUST!!!)

## Credits
* knryuuki - Not So Great Scripter
