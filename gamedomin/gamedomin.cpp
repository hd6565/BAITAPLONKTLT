#include"Console.h"
#include"main.h" 
#include "functions.h"
short STrang, SVTriChon, SMuc;

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHeight);

	SetConsoleTitle(TEXT("GAME DO MIN")); 

	veTieuDeGame(); 

	Cursor(false);
	
	veMenu(0); 
	STrang = 1; 
	xuLysukien();



	
////std::cout<<std::endl; 
//	system("pause");
	return 0;
	
}

