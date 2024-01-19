#pragma once
#include <iostream>
#include<ctime>

#define ConsoleWidth 80 
#define ConsoleHeight 35 

#define ClickTrai 0x5A
#define ClickPhai 0x58

struct CautruccuaBang
{
	short SCOT = 0;
	short SDONG = 0;
	short SSOBOM = 0;
	short SSOODAMO = 0;
	short SSOCO = 0;
};
struct CautrucO
{
	bool BCOBOM = false;
	bool BDAMO = false;
	bool BCAMCO = false;
	short SSOBOMLANCAN = 0; 
};
extern short STrang, SVTriChon, SMuc;
